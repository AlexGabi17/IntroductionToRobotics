#include "joystickLogic/joystickLogic.h"
#include "menu/menu.h"
#include "button/button.h"
#include "lcdDisplay/lcdDisplay.h"
#define ENTER_BUTTON_PIN 13

void setup() {
  pinMode(ENTER_BUTTON_PIN, INPUT);
  pinMode(contrastPin, OUTPUT);
  analogWrite(contrastPin, 130);

  lcd.begin(16, 2);

  lcd.createChar(0, arrowUp);
  lcd.createChar(1, arrowDown);

  
  Serial.begin(9600);
}

void loop() {
  buttonCheck();
  short int movementPosition = getMovementPosition();

  
  // Menu State Switching
  verifyChangeJoystick(movementPosition);
  menuStateSwitching(changebleValueJoystick, lastButtonState, movementPosition, buttonState);
  writeText(getText(), verifyMoveUp(), verifyMoveDown());
  Serial.println("ScreenMsg=" + String(getText()) + ", MenuState=" + String(menuState));
  
}
