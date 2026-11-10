#include <QTRSensors.h>
QTRSensors qtr;
const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];
//motor pins
const int In1 = A5;
const int In2 = A4;
const int In3 = A3;
const int In4 = A2;

//enable pins
const int EnA1 = 6; 
const int EnA2 = 9;

void setup() {
  //set up and calibrate sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){ 2, 3, 4, 5 }, SensorCount);
  for (uint16_t i = 0; i < 400; i++) {
    qtr.calibrate();
  }
  //motor pins to output
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(EnA1, OUTPUT); 
  pinMode(EnA2, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
    uint16_t position = qtr.readLineBlack(sensorValues);
    Serial.println(position);

//left of line 3000
//right of line 0
  int MotorR = map(position, 0, 3000, 100, 0);
  int MotorL = map(position, 0, 3000, 0, 100);

    
  if (position < 1000) {
    //turn right motor on
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    analogWrite(EnA1, 80);
    analogWrite(EnA2, 80);
  }
  else if (position > 2000) {
    //turn left motor on
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(EnA1, 80);
    analogWrite(EnA2, 80);
  }
  else{
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    analogWrite(EnA1, 80);
    analogWrite(EnA2, 80);
    }
}


int readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimetres(duration);

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);
  return cm;
}
long microsecondsToCentimetres(long microseconds) {
  return microseconds / 29 / 2;
}


void r() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  analogWrite(EnA1, 100);
  analogWrite(EnA2, 100);
  delay(250);
  motorOff();
}

void l() {
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  analogWrite(EnA1, 100);
  analogWrite(EnA2, 100);
  delay(370);
  motorOff();
}

void s() {
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  analogWrite(EnA1, 115);
  analogWrite(EnA2, 70);
}

void motorOff() {
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  analogWrite(EnA1, 0);
  analogWrite(EnA2, 0);
}
