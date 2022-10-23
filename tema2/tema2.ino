// Tema 2
// Buzescu Alexandru-Gabriel

// Potentiometer
const int potPin_Red = A0;
const int potPin_Green = A1;
const int potPin_Blue = A2;
int potValue_Red = 0;
int potValue_Green = 0;
int potValue_Blue = 0;

// RGB Led
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}
int readAndMap(int pin){
  int value = analogRead(pin);
  value = map(value, 0, 1023, 0, 255);

  return value;
}
void turnOnRGB(int redValue, int greenValue, int blueValue){
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
void loop() {
  potValue_Red = readAndMap(potPin_Red);
  potValue_Green = readAndMap(potPin_Green);
  potValue_Blue = readAndMap(potPin_Blue);
  
  turnOnRGB(potValue_Red, potValue_Green, potValue_Blue);
}
