#include <SoftwareSerial.h>
int rpm;
SoftwareSerial DataSerial(D2,D3); //Rx,Tx
void setup() {
 pinMode(D8,INPUT); // PRZYCISK
 pinMode(D7,OUTPUT); // DIODA
 pinMode(D6,OUTPUT); //OUTPUT DALEKI
 pinMode(D5,INPUT); // INPUT DALEKI
DataSerial.begin(9600);
Serial.begin(9600);
}

void loop() {
  if(digitalRead(D8) == HIGH){
    digitalWrite(D6,HIGH);
    digitalWrite(D7,HIGH); //dioda
    while(digitalRead(D5) == HIGH){
      delay(50);
      DataSerial.println(2);
    }
  }else{
    digitalWrite(D6,LOW);
    digitalWrite(D7,LOW);
  }
if(digitalRead(D5) == HIGH){
  digitalWrite(D6,HIGH);
  while(digitalRead(D5) == HIGH){
   delay(50);
   char value[2];
   DataSerial.readBytes(value,2);
   rpm = atoi(value);
   Serial.println(rpm);
   if(rpm == 3){
    digitalWrite(D7,HIGH);
    digitalWrite(D6,LOW);
    delay(1000);
    digitalWrite(D7,LOW);
   }
  }
}

}




