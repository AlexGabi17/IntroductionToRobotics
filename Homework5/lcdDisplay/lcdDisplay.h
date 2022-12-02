#include <LiquidCrystal.h>
#include <string.h>
#define REFRESH_RATE 250
const byte RS = 9;
const byte enable = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
const byte contrastPin = 3;
unsigned long lastRefresh = 0;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

byte arrowUp[] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B01110,
  B11111,
  B00000,
  B00000
};


byte arrowDown[] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

void writeText(char* msg, byte verifyMoveUp, byte verifyMoveDown){
    if(millis() - lastRefresh > REFRESH_RATE){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(msg);
        

        if(verifyMoveUp){ // verify if menu can go up
            lcd.setCursor(15,0);
            lcd.write(byte(0));
        }
        if(verifyMoveDown){ //verify if menu can go
            lcd.setCursor(15,1);
            lcd.write(byte(1));
        }
        lastRefresh = millis();
    }
}