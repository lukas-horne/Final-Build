#include <QTRSensors.h>
QTRSensors qtr;
const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];
//motor pins
const int In1 = 13;
const int In2 = 12;
const int In3 = 11;
const int In4 = 10;

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

    
  if (position < 1000) {
    //turn right motor on
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
    analogWrite(EnA1, 60);
    analogWrite(EnA2, 80);
  }
  else if (position > 2000) {
    //turn left motor on
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
    analogWrite(EnA1, 80);
    analogWrite(EnA2, 60);
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
