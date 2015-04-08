/*
Bare minimum code to get TCchargers to work with arduino.
 
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup()  
{
  Serial.begin(9600);
  Serial.println("TCcharger");
  mySerial.begin(2400);
}
//String inData;
byte bytes[12];
byte n;
//18 06 E5 F4 VV VV AA AA XX 00 00 00
byte toCharger[12] = {0x18,0x06,0xE5,0xF4,0x05,0xDC,0x00,0x64,0x00,0x00,0x00,0x00};
void loop() // run over and over
{
  if(mySerial.available()){
    byte recieved = mySerial.read();
    if(recieved == 0x18){
      bytes[n]=recieved;
      n += 1;
      delay(100);
      while(mySerial.available()>0){
        recieved = mySerial.read();
        bytes[n]=recieved;
        n += 1;
      }
    }
    n = 0;
    for (int i = 0; i < 12; i += 1){
      Serial.println(bytes[i],HEX);
    }
    for (int i = 0; i < 12; i += 1){
      mySerial.write(toCharger[i]);
    }
  }
}
