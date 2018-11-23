#include <MFRC522.h>
#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD
const byte UID[] = {0xd3, 0xc8, 0x12, 0x1c};
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
MFRC522 rfid(10, 9);
MFRC522::MIFARE_Key key;

void setup() {
SPI.begin();
rfid.PCD_Init();
Waiting();

}

void loop() {
if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
{
if (rfid.uid.uidByte[0] == UID[0] &&
rfid.uid.uidByte[1] == UID[1] &&
rfid.uid.uidByte[2] == UID[2] &&
rfid.uid.uidByte[3] == UID[3])
{
  Correct();
}else{
  inCorrect();
}
rfid.PICC_HaltA();
rfid.PCD_StopCrypto1();
}
}
void Waiting(){
lcd.clear();
lcd.begin(16,2);
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("      Witaj");
lcd.setCursor(0,1);
lcd.print("  Przyloz Karte");
digitalWrite(2,HIGH);
}
void Correct(){
lcd.clear();
lcd.begin(16,2);
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("    Poprawne");
lcd.setCursor(0,1);
lcd.print("  Drzwi otwarte");
delay(3000);
Waiting();
}
void inCorrect(){
lcd.clear();
lcd.begin(16,2);
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("   Niepoprawne");
lcd.setCursor(0,1);
lcd.print(" Brak zazwolenia");
delay(3000);
Waiting();
}

