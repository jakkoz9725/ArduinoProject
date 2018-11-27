#include <SoftwareSerial.h>
#include <MFRC522.h>
#include <Wire.h>
#include <SPI.h>

const byte Jakub[] = {0xd3, 0xc8, 0x12, 0x1c};
const byte Agnieszka[] = {0x69, 0x2A, 0xD6, 0x73};

MFRC522 rfid(10, 9);
MFRC522::MIFARE_Key key;

int rpm;
SoftwareSerial DataSerial(2,3); //Rx,Tx
void setup() {
 pinMode(8,OUTPUT); // DIODA
 pinMode(7,INPUT); // PRZYCISK
 pinMode(6,INPUT); // INPUT DALEKI
 pinMode(5,OUTPUT); // OUTPUT DALEKI

SPI.begin();
rfid.PCD_Init();
DataSerial.begin(9600);
Serial.begin(9600);
}

void loop(){
if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
{
if (rfid.uid.uidByte[0] == Jakub[0] &&
rfid.uid.uidByte[1] == Jakub[1] &&
rfid.uid.uidByte[2] == Jakub[2] &&
rfid.uid.uidByte[3] == Jakub[3])
 {
Dobra(3);
 }else if (rfid.uid.uidByte[0] == Agnieszka[0] &&
rfid.uid.uidByte[1] == Agnieszka[1] &&
rfid.uid.uidByte[2] == Agnieszka[2] &&
rfid.uid.uidByte[3] == Agnieszka[3])
  {
Dobra(4);
rfid.PICC_HaltA();
rfid.PCD_StopCrypto1();
  }
}

  if(digitalRead(6) == HIGH){
    digitalWrite(5,HIGH);
      while(digitalRead(6) == HIGH){
        char value[2];
        DataSerial.readBytes(value,2);
        rpm = atoi(value);
        if(rpm == 2){
          digitalWrite(8,HIGH);
          digitalWrite(5,LOW);
          delay(2000);
          digitalWrite(8,LOW);
        }
      }
  }
    digitalWrite(5,LOW);
    digitalWrite(8,LOW);
}
void Dobra(int whosThere){
    digitalWrite(5,HIGH);
    digitalWrite(8,HIGH); //dioda
    delay(2000);
    Serial.println("test");
    while(digitalRead(6) == HIGH){
      DataSerial.println(whosThere);
      delay(50);
    }
  }

