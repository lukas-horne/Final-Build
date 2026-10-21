#include <QTRSensors.h>
QTRSensors qtr;
const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];
//motor pins
const int In1 = 13;
const int In2 = 12;
const int In3 = 11;
const int In4 = 10;

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
  Serial.begin(9600);
}

void loop() {
  int position = qtr.readLineBlack(sensorValues);

  if (position < 1300) {
    //turn right
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
  } else {
    //turn motor off
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
  }

  if (position > 1700) {
    //turn left
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
  } else {
    //turn motor off
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
  }

  if ((position < 1700) && (position > 1300)) {
    //go straight
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
  } else {
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
  }

  displaySensors();
}

void displaySensors() {
  //print sensor values
  uint16_t position = qtr.readLineBlack(sensorValues);
  Serial.print("Sensors: ");
  for (uint8_t i = 0; i < SensorCount; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(position);
  delay(250);
}
