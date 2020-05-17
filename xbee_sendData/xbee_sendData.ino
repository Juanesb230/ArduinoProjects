#include <XBee.h>
XBee xbee = XBee();

uint8_t payload[] = {0,0,0,0};
int numero=239;
String data;

XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x0000ffff);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

char datos[5];
int statusLed = 13;
int errorLed = 13;

void setup() {
  Serial.begin(9600);
  xbee.setSerial(Serial);
}

void loop() { 
  data=String(numero);
  data.toCharArray(datos,5);  
  for(int i=0;i<4;i++){
    payload[i]=datos[i];
  }
  xbee.send(zbTx);
  if (xbee.readPacket(500)) {            
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);
    }
  }
  delay(1000);
}
