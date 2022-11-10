#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define DP 7

const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDP = 11;

const int pinX = A0;
const int pinY = A1;
const int pinSW = 2;
const int moveSize = 4;
const int segSize = 8;
const int noOfDigits = 10;
int index = 0;
int currentPin = pinDP;
byte currentLedState = LOW;
byte state = HIGH;
byte dpState = LOW;
int debounceValue = -1;
int xValue = 0;
int yValue = 0;

int swState = LOW;
int lastSwState = LOW;
unsigned long lastBlink = 0;
const int blinkTime = 199;
unsigned long lastChangedLeds = 0;
const int debounceChangedLeds = 1000;
byte blinkable = 1;
unsigned long lastDebounceTimeMovement = 0;
const int debounceTimeMovement = 25;
int lastDebounceValue = -1;
const int longDebounceTimePressLong = 3000;
byte longPressedActive = 0;

const int maxHold = 700;
const int minHold = 300;

int position = -1;
int newPosition;
int result = -1;

int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};
const int movementMatrix[noOfDigits][4] = {
  { -1, G, F, B},
  { A, G, F, -1},
  { G, D, E, DP},
  { G, -1, E, C},
  { G, D, -1, C},
  { A, G, -1, B},
  { A, D, -1, -1},
  { -1, -1, C, -1}
};
bool reading = 0;
bool buttonPressed = 0;
bool lastButtonState = LOW;
bool buttonState = LOW;
bool lastReading = 0;
unsigned long longPressedDebounce = 0;
unsigned long lastDebounceTimePressed = 0;
unsigned long debounceDelayPressed = 50;
byte memoryState[segSize] = {
  0, 0, 0, 0, 0, 0, 0, 0
};
const int buttonDebounceDelay = 50;
byte systemState = 0;
unsigned long buttonLastDebounceTime = 0;
bool checkHowLong = 0;
unsigned long longPressedTime = 0;

void setup() {
  if (commonAnode == true) {
    state = !state;
  }
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  pinMode(pinSW, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  Serial.println("xValue=" + String(xValue) + " y=" + String(yValue));
  buttonCheck();
  if (!buttonPressed) {
    state1();
  }
  else {
    state2();
  }
  // Light up from memory states
  lightUpLeds();

}
int getPinFromIndex() {
  switch (currentPin) {
    case pinA:
      return A;
      break;
    case pinB:
      return B;
      break;
    case pinC:
      return C;
      break;
    case pinD :
      return D;
      break;
    case pinE:
      return E;
      break;
    case pinF:
      return F;
      break;
    case pinG:
      return G;
      break;
    default:
      return DP;
  }
}
int getMovementPosition() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  if (millis() - lastDebounceTimeMovement > debounceTimeMovement) {
    lastDebounceTimeMovement = millis();
    lastDebounceValue = debounceValue;
    if (xValue > maxHold && (yValue < maxHold && yValue > minHold)) {
      debounceValue = UP;
    }
    else if (xValue < minHold && (yValue < maxHold && yValue > minHold)) {
      debounceValue = DOWN;
    }
    else if (yValue > maxHold && (xValue < maxHold && xValue > minHold)) {
      debounceValue = RIGHT;
    }
    else if (yValue < minHold && (xValue < maxHold && xValue > minHold)) {
      debounceValue = LEFT;
    }
    else {
      debounceValue = -1;
    }
  }
  if (lastDebounceValue == debounceValue) {
    return debounceValue;
  }
  return -1;
}

void blinkingCurrentLed() {
  if (millis() - lastBlink > blinkTime) {
    lastBlink = millis();
    currentLedState = !currentLedState;
    digitalWrite(currentPin, currentLedState);
  }
}

void lightUpLeds() {
  for (int i = 0; i < segSize; ++i) {
    if (currentPin != segments[i] && !buttonPressed)
      digitalWrite(segments[i], memoryState[i]);
  }
}

void state1() {
  blinkingCurrentLed();

  newPosition = getMovementPosition();
  if (newPosition != -1) {

    if (movementMatrix[getPinFromIndex()][newPosition] != -1) {
      digitalWrite(currentPin, LOW);
      if (millis() - lastChangedLeds > debounceChangedLeds) {
        lastChangedLeds = millis();
        if (memoryState)
          currentPin = segments[movementMatrix[getPinFromIndex()][newPosition]];

      }
    }
  }
}
void state2() {
  digitalWrite(currentPin, LOW);
  int positionState2 = getMovementPosition();

  if ( positionState2 == UP) {
    result = 1;
  }
  else if ( positionState2 == DOWN) {
    result = 0;
  }

  if (result != -1) {
    // digitalWrite(currentPin, result);
    memoryState[getPinFromIndex()] = result;
  }
  digitalWrite(currentPin, memoryState[getPinFromIndex()]);
  // Serial.println(result);
  result = -1;
}
void clearMemoryState() {
  for (int i = 0; i < segSize; i++) {
    memoryState[i] = 0;
  }
}
void buttonCheck() {
  reading = digitalRead(pinSW);
  if (reading != lastButtonState) {
    lastDebounceTimePressed = millis();
  }

  if (buttonState == 0) {
    if (reading != lastReading) {
      longPressedTime = millis();
    }
    lastReading = reading;
    if (millis() - longPressedTime > longDebounceTimePressLong ) {
      buttonPressed = 0;
      longPressedTime = millis();
      clearMemoryState();
      currentPin = pinDP;
      //Serial.println("Reseted");
    }
  }
  if (millis() - lastDebounceTimePressed > debounceDelayPressed) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW ) {
        if (!buttonPressed) { // to not reset the timer if the button is pressed multiple times
          buttonPressed = 1;
          checkHowLong = 1;
        }
        else {
          buttonPressed = 0;
        }
      }
    }
  }
  lastButtonState = reading;
}
