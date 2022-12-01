#include "joystickLogic/joystickLogic.h"
#include "menu/menu.h"
#include "button/button.h"
#define ENTER_BUTTON_PIN 13

void setup() {
  pinMode(ENTER_BUTTON_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  buttonCheck();
  short int movementPosition = getMovementPosition();

  
  // Menu State Switching
  verifyChangeJoystick(movementPosition);
  menuStateSwitching(changebleValueJoystick, lastButtonState, movementPosition, buttonState);

  Serial.println("ButtonState=" + String(buttonState) + ", lastBState= " + String(lastButtonState) +", MenuState=" + String(menuState));
  
}
