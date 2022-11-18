#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define BLINK_TIME 250


const int pinX = A0; 
const int pinY = A1;
const int pinSW = 2;
int xValue = 0;
int yValue = 0;
unsigned long lastDebounceTimeMovement = 0;
const int debounceTimeMovement = 25;
const int maxHold = 700;
const int minHold = 300;
int lastDebounceValue = -1;
int debounceValue = lastDebounceValue;
int joystickPosition;

unsigned long lastChangeNumber = 0;
const int ChangeNumberTime = 100;

// button
bool reading = 0;
bool buttonPressed = 0;
bool lastButtonState = LOW;
bool buttonState = LOW;
bool lastReading = 0;
unsigned long longPressedDebounce = 0;
unsigned long lastDebounceTimePressed = 0;
unsigned long debounceDelayPressed = 100;
const int buttonDebounceDelay = 50;
byte systemState = 1;
unsigned long buttonLastDebounceTime = 0;
unsigned long longPressedTime = 0;
const int longDebounceTimePress = 3000;


unsigned long lastMovedDP = 0;
const int dpMoveTime = 200;
//DS= [D]ata [S]torage - data
//STCP= [ST]orage [C]lock [P]in latch
//SHCP= [SH]ift register [C]lock [P]in clock

const int latchPin = 11; // STCP to 12 on Shift Register
const int clockPin = 10; // SHCP to 11 on Shift Register
const int dataPin = 12; // DS to 14 on Shift Register

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

int currentDisplayNumber[] = {0, 0, 0, 0};
byte currentDigit = 0;

// led debounce
unsigned long lastBlink = 0;
byte blinkState = 0; // by default it's blinking


const byte regSize = 8; // 1 byte aka 8 bits

int displayDigits[] = {
  segD1, segD2, segD3, segD4
};

const int encodingsNumber = 16;

int byteEncodings[encodingsNumber] = {
//A B C D E F G DP 
  B11111100, // 0 
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};


const int displayCount = 4;

int registers[regSize];

void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(pinSW, INPUT);
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }
  Serial.begin(9600);
}

int index = 0;

void loop() {
  joystickPosition = getMovementPosition();
  writeNumber();
  blinkCurrentLed();

  buttonCheck();
  if (!buttonPressed) {
    systemState = 1;
    state1();
  }
  else {
    systemState = 2;
    state2();
  }
  // Serial.println(buttonPressed);
}

void state1(){
  if(millis() - lastMovedDP > dpMoveTime){
    if ( joystickPosition == LEFT ) {
      currentDigit ++ ;
    }
    else if ( joystickPosition == RIGHT) {
      currentDigit --;
    }
    lastMovedDP = millis();
    currentDigit = currentDigit%4;
  }
}
void state2(){
    if(millis() - lastChangeNumber > ChangeNumberTime){
      if ( joystickPosition == UP) {
        currentDisplayNumber[3 - currentDigit] += 1;
      }
      else if ( joystickPosition == DOWN) {
        currentDisplayNumber[3 - currentDigit] -=1 ;
  
      }
    lastChangeNumber = millis();
    Serial.println(currentDisplayNumber[4 - currentDigit]);

    if(currentDisplayNumber[3 - currentDigit] == 16){
      currentDisplayNumber[3 - currentDigit] = 0;
    }
    else if(currentDisplayNumber[3 - currentDigit] == -1){
      currentDisplayNumber[3 - currentDigit] = 15;
    }
  }
}
void activateDisplay(int digit) {
  for(int i=0; i<4; i++) {
      digitalWrite(displayDigits[i], HIGH);
  }

  digitalWrite(displayDigits[digit], LOW);
}
void writeReg(int encoding) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, encoding);
  digitalWrite(latchPin, HIGH);
  
}

void writeNumber() {
  // int currentNumber = number % 10000;
  int displayIndex = 0;
  // int currentDigit = 0;
  while (displayIndex <= 4) {
    // currentDigit = currentNumber % 10;
    // currentNumber /= 10;
    int encoding;
    if(currentDigit == displayIndex){
      encoding = (byteEncodings[currentDisplayNumber[3 - displayIndex]] | blinkState); // bitwise OR operations with 1 to get HIGH Voltage on DP pin
    }
    else{
      encoding = byteEncodings[currentDisplayNumber[3 - displayIndex]];
    }
    writeReg( encoding );

    activateDisplay(displayIndex);
   
    delay(5);
    displayIndex ++;

  }
}
void blinkCurrentLed(){
  if(millis() - lastBlink > BLINK_TIME && systemState == 1){
    lastBlink = millis();
    blinkState = !blinkState;
  }
  else if(systemState == 2){
    blinkState = 1;
  }
}

int getMovementPosition() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  // Serial.println("xValue=" + String(xValue) + ", yValue=" + String(yValue));
  if (millis() - lastDebounceTimeMovement > debounceTimeMovement) {
    lastDebounceTimeMovement = millis();
    lastDebounceValue = debounceValue;
    if (xValue > maxHold && (yValue < maxHold && yValue > minHold)) {
      debounceValue = DOWN;
    }
    else if (xValue < minHold && (yValue < maxHold && yValue > minHold)) {
      debounceValue = UP;
    }
    else if (yValue > maxHold && (xValue < maxHold && xValue > minHold)) {
      debounceValue = LEFT;
    }
    else if (yValue < minHold && (xValue < maxHold && xValue > minHold)) {
      debounceValue = RIGHT;
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
void clearDisplays(){
  for(int index=0; index < 4; index++){
    currentDisplayNumber[index] = 0;
  }
}
void buttonCheck() {
  reading = digitalRead(pinSW);
  // Serial.println(reading);
  if (reading != lastButtonState && !reading) {
    lastDebounceTimePressed = millis();
  }

  if (millis() - lastDebounceTimePressed > debounceDelayPressed) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == 0 ) {
        if (!buttonPressed) { // to not reset the timer if the button is pressed multiple times
          buttonPressed = 1;
        }
        else {
          buttonPressed = 0;
        }
      }
    }
  }
  Serial.println(buttonState);
  lastButtonState = reading;
}
