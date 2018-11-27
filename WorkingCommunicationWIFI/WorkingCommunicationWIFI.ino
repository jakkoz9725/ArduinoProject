#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <time.h>


// Set these to run example.
#define FIREBASE_HOST "xxx"
#define FIREBASE_AUTH "xxx"
#define WIFI_SSID "xxx"
#define WIFI_PASSWORD "xxx"

int redlight;
int rpm;
SoftwareSerial DataSerial(D2,D3); //Rx,Tx
void setup() {
 pinMode(D7,OUTPUT); // DIODA
 pinMode(D6,OUTPUT); //OUTPUT DALEKI
 pinMode(D5,INPUT); // INPUT DALEKI
DataSerial.begin(9600);
Serial.begin(9600);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Wifi connected sucessful");
  configTime(3600, 0, "pool.ntp.org", "time.nist.gov");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("Zamek",0);
  Firebase.set("WhosThere","Unknown");
  Firebase.pushString("Historia","prepare");
}

void loop() {
  if(Firebase.getInt("Zamek") == 1){
    while(Firebase.getInt("Zamek") == 1){
    digitalWrite(D6,HIGH);
    digitalWrite(D7,HIGH); //dioda
    while(digitalRead(D5) == HIGH){
      DataSerial.println(2);
      Firebase.setInt("Zamek",0);
      redlight = 0;
      Firebase.setInt("Zamek",0);
    }
  }
  time_t now = time(nullptr);
  String nazwa_otwierajacego = Firebase.getString("WhosThere");
  String data_otwierajacy = ctime(&now) + nazwa_otwierajacego;
  Firebase.pushString("Historia",data_otwierajacy);
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
   if(rpm == 3 || rpm == 4){
    digitalWrite(D7,HIGH);
    digitalWrite(D6,LOW);
    delay(1000);
    digitalWrite(D7,LOW);
   }
  }
  if(rpm == 3){
    time_t now = time(nullptr);
  String nazwa_otwierajacego = "Jakub";
  String data_otwierajacy = ctime(&now) + nazwa_otwierajacego;
  Firebase.pushString("Historia-Kart", data_otwierajacy);
  }else if(rpm == 4)
  {
    time_t now = time(nullptr);
  String nazwa_otwierajacego = "Agnieszka";
  String data_otwierajacy = ctime(&now) + nazwa_otwierajacego;
  Firebase.pushString("Historia-Kart", data_otwierajacy);
  }
}

}




