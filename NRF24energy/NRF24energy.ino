#include<SPI.h>
#include<RF24.h>
#include "printf.h"
#include "EmonLib.h"

EnergyMonitor emon1;             
float KWs=0;
float starttime=0;

RF24 radio(9, 10);

void setup(void){
  pinMode(7,OUTPUT);
  emon1.voltage(A0, 135, 0); 
  emon1.current(A1, 29);       
  printf_begin();
  while(!Serial);
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x76);
  radio.openWritingPipe(0xF0F0F0F0E3LL);
  const uint64_t ArduinoDir = (0xE8E8F0F0E3LL);
  radio.openReadingPipe(1, ArduinoDir);
  radio.enableDynamicPayloads();
  radio.powerUp();
  radio.printDetails();
  starttime=millis()/1000;
}

void loop(void){ 
  emon1.calcVI(20,2000);         
  float realPower       = emon1.realPower;
  float supplyVoltage   = emon1.Vrms;             
  float Irms            = emon1.Irms;
  float powerFActor     = emon1.powerFactor;
  float endtime=millis()/1000;
  if (endtime-starttime >=1){
  KWs= realPower/1000+KWs;
  starttime=millis()/1000;
  }
  radio.startListening();
  char receivedRPIMessage[32] = {0};
  if(radio.available()){
    radio.read(receivedRPIMessage, sizeof(receivedRPIMessage));
    Serial.println(receivedRPIMessage);
    Serial.println("Stop Listening");
    radio.stopListening();
    String stringMessage(receivedRPIMessage);

    if(stringMessage == "GETSTRING"){
      Serial.print("Energy (Kws)=");
      Serial.println(KWs);
      Serial.print("P (W)=");
      Serial.println(realPower);
      Serial.print("Vrms (v)=");
      Serial.println(supplyVoltage);
      Serial.print("Irms (A)=");
      Serial.println(Irms);
      Serial.print("fp (U)=");
      Serial.println(powerFActor);
      const char text[8];
      dtostrf(KWs, 4, 2, text);
      radio.write(text, sizeof(text));
      Serial.println("Arduino sent energy");
      KWs=0;
  }
  delay(100);
}
