#include <SoftwareSerial.h>
int rpm;
SoftwareSerial DataSerial(2,3); //Rx,Tx
void setup() {
 pinMode(8,OUTPUT); // DIODA
 pinMode(7,INPUT); // PRZYCISK
 pinMode(6,INPUT); // INPUT DALEKI
 pinMode(5,OUTPUT); // OUTPUT DALEKI

DataSerial.begin(9600);
Serial.begin(9600);
}

void loop(){
  if(digitalRead(6) == HIGH){
    digitalWrite(5,HIGH);
      while(digitalRead(6) == HIGH){
        delay(50);
        char value[2];
        DataSerial.readBytes(value,2);
        rpm = atoi(value);
        if(rpm == 2){
          digitalWrite(8,HIGH);
          digitalWrite(5,LOW);
          delay(1000);
          digitalWrite(8,LOW);
        }
      }
  }
  if(digitalRead(7) == HIGH){
    digitalWrite(5,HIGH);
    digitalWrite(8,HIGH); //dioda
    while(digitalRead(6) == HIGH){
      DataSerial.println(3);
      delay(50);
    }
  }else{
    digitalWrite(5,LOW);
    digitalWrite(8,LOW);
  }
}
