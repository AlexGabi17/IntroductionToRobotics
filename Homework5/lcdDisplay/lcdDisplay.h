#include <LiquidCrystal.h>
#include <string.h>
#include "init.h"
#include "../data/data.h"
void writeText(char* msg,bool menuScroll, byte verifyMoveUp, byte verifyMoveDown){
    if(millis() - lastRefresh > REFRESH_RATE){
        lcd.clear();
        if(!menuScroll){
          if(strcmp(msg, "Username ") == 0){
            lcd.setCursor(7, 0);
            lcd.write(byte(0));



            lcd.setCursor(7,1);
            lcd.print(Player.name[0]);
            lcd.print(Player.name[1]);
            lcd.print(Player.name[2]);
          }
        }
        else{
          lcd.setCursor(0, 0);
          lcd.print(msg);
          lcd.write(byte(2));

          if(verifyMoveUp){ // verify if menu can go up
              lcd.setCursor(15,0);
              lcd.write(byte(0));
          }
          if(verifyMoveDown){ //verify if menu can go
              lcd.setCursor(15,1);
              lcd.write(byte(1));
          }
        }
        lastRefresh = millis();
    }
}