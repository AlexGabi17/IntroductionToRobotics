// Implementing the menu as a DFA
#define NO_ACTION -1
#define START_GAME 0
#define SETTINGS 1
#define HIGHSCORE 2
#define ABOUT 3
#define HOW_TO_PLAY 4
#define GAMEPLAY 5
#define LOST 6
#define NAME 7
#define DIFFICULTY 8
#define LCD_CONTRAST 9
#define LCD_BRIGTHNESS 10
#define MATRIX_BRIGHTNESS 11

int menuState = 0; // menu will open with START GAME 

//movement MATRIX for the menu

short int menuMovementMatrix[][3] = {
//  {DOWN, UP, BUTTONPRESSED}
    {SETTINGS, NO_ACTION, GAMEPLAY}, // STATE 0 -> START GAME
    {HIGHSCORE, START_GAME, NAME}, // STATE 1 -> SETTINGS
    {ABOUT, SETTINGS, NO_ACTION}, // STATE 2 -> HIGHSCORE
    {HOW_TO_PLAY, HIGHSCORE, NO_ACTION}, // STATE 3 -> ABOUT
    {NO_ACTION, ABOUT, NO_ACTION}, // STATE 4 -> HOW TO PLAY
    {NO_ACTION, NO_ACTION, NO_ACTION}, // STATE 5 -> GAMEPLAY
    {NO_ACTION,NO_ACTION,START_GAME}, // STATE 6 -> LOST 
    {DIFFICULTY, SETTINGS, NO_ACTION}, // STATE 7 -> NAME
    {LCD_CONTRAST, NAME, NO_ACTION}, // STATE 8 -> DIFFICULTY
    {LCD_BRIGTHNESS, DIFFICULTY, NO_ACTION}, // STATE 9 -> LCD_CONTRAST
    {MATRIX_BRIGHTNESS, LCD_CONTRAST, NO_ACTION}, // STATE 10 -> LCD_BRIGTHNESS
    {NO_ACTION, LCD_BRIGTHNESS, NO_ACTION} // STATE 11 -> MATRIX BRIGTHNESS
};

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