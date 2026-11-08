const int trigPin = 7;
const int echoPin = 8;


//motor pins
const int In1 = 13;
const int In2 = 12;
const int In3 = 11;
const int In4 = 10;


//enable pins
const int EnA1 = 6;
const int EnA2 = 9;

bool Bool = true;


// Variables for duration of ping and the distance in cm
long duration, cm;

void setup() {


  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {


  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:


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

  int rightV;
  int leftV;
  int straightV;

  if (/* uses colour sensor to read the colour green meaning in toxic waste*/ Bool == true) {
    straightV = straight();

    r();
    rightV = right();

    l();
    leftV = left();
    
    //get it back to facing forward with r()
    r();
    Bool = false;
  }


  int smallest = min(straightV, min(rightV, leftV));
  if (smallest == rightV) {
    //go right
    r();
    s();
    delay(5000);
    motorOff();
  } else if (smallest == leftV) {
    //go left
    l();
    s();
    delay(5000);
    motorOff();

  } else if (smallest == straightV) {
    //go straight
    s();
    delay(5000);
    motorOff();
  }
}


long microsecondsToCentimetres(long microseconds) {
  return microseconds / 29 / 2;
}




int right() {
  // turn right
  delay(5000);
  int distance = cm;
  return distance;
}


int left() {
  // turn left
  delay(5000);
  int distance = cm;
  return distance;
}


int straight() {
  //read straight
  delay(5000);
  int distance = cm;
  return distance;
}

void r() {
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  analogWrite(EnA1, 100);
  analogWrite(EnA2, 100);
  delay(600);
  motorOff();
}

void l() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  analogWrite(EnA1, 100);
  analogWrite(EnA2, 100);
  delay(1200);
  motorOff();
}

void s() {
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  analogWrite(EnA1, 100);
  analogWrite(EnA2, 100);
}

void motorOff() {
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
}
