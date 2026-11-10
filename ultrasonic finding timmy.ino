const int trigPin = 7;
const int echoPin = 8;

//motor pins
const int In1 = A5;
const int In2 = A4;
const int In3 = A3;
const int In4 = A2;

//enable pins
const int EnA1 = 6;
const int EnA2 = 9;

bool Bool = true;
//variables for each direction value
int rightV, leftV, straightV;

// Variables for duration of ping and the distance in cm
long duration, cm;


void setup() {
  //ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //motor
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(EnA1, OUTPUT);
  pinMode(EnA2, OUTPUT);
  //initialise serial communication:
  Serial.begin(9600);
}


void loop() {
  if (/* uses colour sensor to read the colour green meaning in toxic waste*/ Bool == true) {
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
      motorOff();
    } else if (smallest == leftV) {
      //go left
      l();
      delay(3000);
      s();
      motorOff();
    } else if (smallest == straightV) {
      //go straight
      s();
      motorOff();
    }
    Bool = false;
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
