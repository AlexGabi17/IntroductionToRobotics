// Implementing the menu as a DFA
#include "init.h"

//movement MATRIX for the menu

byte verifyMoveUp(){
    if(menuMovementMatrix[menuState][1] != NO_ACTION){
        return true;
    }
    return false;
}

byte verifyMoveDown(){
    if(menuMovementMatrix[menuState][0] != NO_ACTION){
        return true;
    }
    return false;
}

void menuStateSwitching(byte changebleValueJoystick, byte lastButtonState, short int joystickMovement, byte buttonState){
    if(changebleValueJoystick){
        if(joystickMovement != -1 && (joystickMovement == 0 || joystickMovement == 1))
        {
            short int result = menuMovementMatrix[menuState][joystickMovement];
            if (result != NO_ACTION){
                menuState = result;
            }
            
        }
    }
    if(lastButtonState != buttonState){
        if(buttonState == 1){
            short int result = menuMovementMatrix[menuState][2];
            Serial.println(result);
            if(result != NO_ACTION){
                menuState = result;
            }
        }   
    }

}



char* getText(){
    switch (menuState)
    {
    case START_GAME:
        return "START GAME";
        break;
    
    case SETTINGS:
        return "SETTINGS";
        break;

    case HIGHSCORE:
        return "HIGHSCORE";
        break;

    case ABOUT:
        return "ABOUT";
        break;

    case HOW_TO_PLAY:
        return "HOW TO PLAY";
        break;

    case GAMEPLAY:
        return "GAMEPLAY";
        break;

    case LOST:
        return "You lost!";
        break;

    case NAME:
        return "Username";
        break;

    case DIFFICULTY:
        return "Difficulty";
        break;

    case LCD_CONTRAST:
        return "LCD_CONTRAST";
        break;   

    case LCD_BRIGTHNESS:
        return "LCD BRIGTHNESS";
        break;  

     case MATRIX_BRIGHTNESS:
        return "MATRIX BRIGHT";
        break;  
               
    default:
        return "RESTART THE ARDUINO !!";
        break;
    }
}