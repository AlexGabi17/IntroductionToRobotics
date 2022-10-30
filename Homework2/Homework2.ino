#define TIME8SECONDS 8000 //MUST BE 8 SECONDS
#define TIME3SECONDS 3000
#define TIME4SECONDS 4000
#define TIME500MILLIS 500
#define TIME100MILLIS 100
int systemState = 1;
unsigned long elapsedTime = 0;
unsigned long lastBlinkTime = 0;
unsigned long lastBuzz = 0;
byte buzzerState = 0;
byte changeState = 0; // byte used for changing states
const int buzzerPin = 6;
//LEDS
const int redCrossWalkLed = 13;
const int greenCrossWalkLed = 12;

const int redCarsLed = 7;
const int yellowCarsLed = 10;
const int greenCarsLed = 9;

byte redCrossWalkState = 0;
byte greenCrossWalkState = 0;

byte redCarsState = 0;
byte yellowCarsState = 0;
byte greenCarsState = 0;


//
const byte interruptPin = 2;
volatile byte buttonState = 0;

//DEBOUNCE
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

 void setup(){
  //pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(redCrossWalkLed, OUTPUT);
  pinMode(greenCrossWalkLed, OUTPUT);

  pinMode(redCarsLed, OUTPUT);
  pinMode(yellowCarsLed, OUTPUT);
  pinMode(greenCarsLed, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(interruptPin), buttonPress, RISING);
  Serial.begin(9600);
}

void loop(){
  switch (systemState){
    
    case 1: //STATE 1
      initState1();
      break;
      
    case 2: //STATE 2
      if(millis() - elapsedTime > TIME8SECONDS && (!changeState) ){
        initState2();
        changeState = 1;
        elapsedTime = millis();
      }
      if(millis() - elapsedTime > TIME8SECONDS){
        systemState = 3;
        changeState = !changeState;
        elapsedTime = millis();
      }
      break;
    
    case 3: //STATE 3
      initState3();
      toneBuzzer(TIME500MILLIS);
      if(millis() - elapsedTime > TIME8SECONDS){
        systemState = 4;
        elapsedTime = millis();
      }
      break;
    
    case 4: //STATE 4
      toneBuzzer(TIME100MILLIS);
      if(millis() - elapsedTime > TIME4SECONDS){
        systemState = 1;
        noTone(buzzerPin);
        elapsedTime = millis();
      }
    default:
      break;
      
  }
  
  refreshState();
  Serial.println("ButtonState=" + String(buttonState) + ", SystemState=" + String(systemState) + ", millis()=" + String(millis()) + ", elapsedTime=" + String(elapsedTime));
}
void buttonPress(){
  if(millis() - lastDebounceTime > debounceDelay){
    buttonState = !buttonState;
    if(systemState == 1){
      systemState = 2;
      elapsedTime = millis();
    }
    lastDebounceTime = millis();
  }
}
void refreshState(){
  digitalWrite(redCrossWalkLed, redCrossWalkState);
  digitalWrite(greenCrossWalkLed, greenCrossWalkState);

  digitalWrite(redCarsLed, redCarsState);
  digitalWrite(yellowCarsLed, yellowCarsState);
  digitalWrite(greenCarsLed, greenCarsState);

  if(systemState == 4){
    if(millis() - lastBlinkTime > TIME500MILLIS){
      greenCrossWalkState = !greenCrossWalkState;
      lastBlinkTime = millis();
    }
  }
}
void initState1(){
  redCrossWalkState = 1;
  greenCrossWalkState = 0;

  redCarsState = 0;
  yellowCarsState = 0;
  greenCarsState = 1;
}

void initState2(){
  redCrossWalkState = 1;
  greenCrossWalkState = 0;

  redCarsState = 0;
  yellowCarsState = 1;
  greenCarsState = 0;
}
void initState3(){
  redCrossWalkState = 0;
  greenCrossWalkState = 1;

  redCarsState = 1;
  yellowCarsState = 0;
  greenCarsState = 0;
}
void toneBuzzer(unsigned int Speed){
  if(millis() - lastBuzz > Speed){
    buzzerState = !buzzerState;
    lastBuzz = millis();
  }
  if(buzzerState){
    tone(buzzerPin, 200); 
  }
  else{
    noTone(buzzerPin);
  }
}
