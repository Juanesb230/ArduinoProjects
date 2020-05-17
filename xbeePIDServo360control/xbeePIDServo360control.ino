#define ENCODER_DO_NOT_USE_INTERRUPTS

#include <XBee.h>
#include <Servo.h>
#include <Encoder.h>
#include <PID_v1.h>

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();

uint8_t payload[] = {0,0,0,0};
int numero_enviar[]={0,0};
String data_enviar;
char datos_enviados[5];

XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x0000ffff);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

Encoder myEnc(2,3);
Servo servo;

double Setpoint, Input, Output;
int velocity;
int pinServo = 11,a=0;
int pot, pos = 90,b=0;
int setpoint;
static int value = 0;
const int ledPin =  13;
long newPosition;
char data_recibido[5]={'0','0','0','0'};



double Kp=1, Ki=0, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

//Setup
void setup() {
  Serial.begin(9600);
  xbee.setSerial(Serial);
  servo.attach(pinServo);
  Input = 0;
  Setpoint = 0;
  pinMode(7, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(6, INPUT_PULLUP);
  while (digitalRead(6) == HIGH) {
    velocity = 1300;
    servo.write(velocity);
  }
  velocity = 1500;
  servo.write(velocity);
  myPID.SetOutputLimits(-200, 200);
  myPID.SetMode(AUTOMATIC);
  newPosition=0;
}
long oldPosition  = -999;
//Programa
void loop() {  
    newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
  }
  xbee.readPacket();
    if (xbee.getResponse().isAvailable()) {
        if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
          xbee.getResponse().getZBRxResponse(rx);
          for(int i=0;i<4;i++){
            data_recibido[i]=rx.getData(i);
          }
          numero_enviar[0]=int(Input);
          numero_enviar[1]=int(Output)+1500;
          for(int j=0;j<2;j++){
            data_enviar=String(numero_enviar[j]);
            data_enviar.toCharArray(datos_enviados,5); 
            for(int i=0;i<4;i++){
             payload[i]=datos_enviados[i];
            }
            xbee.send(zbTx);
            if (xbee.readPacket(500)) {           
              if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
                xbee.getResponse().getZBTxStatusResponse(txStatus);
              }
            }    
            for(int i=0;i<4;i++){
              datos_enviados[i]=' ';
            }
          }
       } else if (xbee.getResponse().getApiId() == MODEM_STATUS_RESPONSE) {
        xbee.getResponse().getModemStatusResponse(msr);  
        }    
    } else if (xbee.getResponse().isError()) {
    }
  
  automatico();
}

void automatico(){
  Input=(double)newPosition;
  Setpoint = (double)atol(data_recibido);
  myPID.Compute();
  servo.write((int)Output+1500);
  b=0;
}
