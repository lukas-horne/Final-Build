#include <SD.h>
File myFile;

const int CSPin = 10;

bool Bool = true;

//motor
const int In1 = A5;
const int In2 = A4;
const int In3 = A3;
const int In4 = A2;
const int EnA1 = 6;
const int EnA2 = 9;

void setup() {
  //motor pins to output
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(EnA1, OUTPUT);
  pinMode(EnA2, OUTPUT);
  Serial.begin(9600);
  //sd card
  pinMode(CSPin, OUTPUT);
}

void loop() {
  if (Bool == true && SD.begin(CSPin)) {

    // open the file for reading:
    myFile = SD.open("test.txt");

    if (myFile) {
      Serial.println("Starting file");
      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        switch (myFile.read()) {
          case 'L':
            left();
            break;
          case 'R':
            right();
            break;
          case 'F':
            forward();
            break;
          case 'B':
            backward();
            break;
        }
      }
      // close the file:
      myFile.close();
      Bool = false;
    }
  }
}

void left() {
  Serial.println("L");
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  analogWrite(EnA1, 100);
  analogWrite(EnA2, 100);
  delay(600);
  f();
  delay(500);
  motorOff();
}

void right() {
  Serial.println("R");
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  analogWrite(EnA1, 100);
  analogWrite(EnA2, 100);
  delay(500);
  f();
  delay(500);
  motorOff();
}

void forward() {
  Serial.println("F");
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  analogWrite(EnA1, 115);
  analogWrite(EnA2, 70);
  delay(500);
  motorOff();
}

void backward() {
  Serial.println("B");
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  analogWrite(EnA1, 115);
  analogWrite(EnA2, 70);
  delay(500);
  motorOff();
}

void f() {
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  analogWrite(EnA1, 115);
  analogWrite(EnA2, 70);
  delay(500);
  motorOff();
}
void motorOff() {
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  analogWrite(EnA1, 0);
  analogWrite(EnA2, 0);
}
