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

//timmy
const int trigPin = 7;
const int echoPin = 8;
//variables for each direction value
int rightV, leftV, straightV;
// Variables for duration of ping and the distance in cm
long duration, cm;

// Define color sensor pins
#define S0 A1
#define S1 A0
#define S2 13
#define S3 12
#define sensorOut 11

int redMin = 23;     // Red minimum value
int redMax = 168;    // Red maximum value
int greenMin = 26;   // Green minimum value
int greenMax = 208;  // Green maximum value
int blueMin = 20;    // Blue minimum value
int blueMax = 155;   // Blue maximum value

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

bool greenDetected = true;

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
  //ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //colour sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Frequency scaling 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  Serial.begin(9600);
}

void loop() {
//left of line 3000
//right of line 0
  int MotorR = map(position, 0, 3000, 100, 0);
  int MotorL = map(position, 0, 3000, 0, 100);
  
  uint16_t position = qtr.readLineBlack(sensorValues);
  Serial.println(position);
  if (getRed() < 220 && getRed() > 180 && getGreen() < 236 && getGreen() > 212 && getBlue() < 200 && getBlue() > 174 && greenDetected == true) {
    motorOff();
    delay(5000);
    straightV = readDistance();
    r();
    delay(5000);
    rightV = readDistance();
    l();
    delay(5000);
    leftV = readDistance();
    //get it back to facing forward with r()
    r();
    delay(3000);

    //gets smallest cm distance since the closest
    int smallest = min(straightV, min(rightV, leftV));
    if (smallest == rightV) {
      //go right
      r();
      delay(3000);
      s();
      delay(4000);
      motorOff();
    } else if (smallest == leftV) {
      //go left
      l();
      delay(3000);
      s();
      delay(4000);
      motorOff();
    } else if (smallest == straightV) {
      //go straight
      s();
      delay(4000);
      motorOff();
    }
    greenDetected = false;
  } else if (position < 1000) {
    //turn right motor on
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
    analogWrite(EnA1, MotorR);
    analogWrite(EnA2, MotorL);
  } else if (position > 2000) {
    //turn left motor on
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
    analogWrite(EnA1, MotorR);
    analogWrite(EnA2, MotorL);
  } else {
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    analogWrite(EnA1, 90);
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


//colour sensor functions
int getRed() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  int redValue;
  redValue = map(PW, redMin, redMax, 255, 0);
  return redValue;
}

int getGreen() {
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  int greenValue;
  greenValue = map(PW, greenMin, greenMax, 255, 0);
  return greenValue;
}

int getBlue() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  int blueValue;
  blueValue = map(PW, blueMin, blueMax, 255, 0);
  return blueValue;
}
