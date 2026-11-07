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

const int yes = 1;



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

  if (/* uses colour sensor to read the colour green meaning in toxic waste*/ yes == 1) {
    straightV = straight();

    r();
    rightV = right();

    l();
    leftV = left();
  }


  int largest = max(straightV, max(rightV, leftV));
  if (largest == rightV) {
    //go right
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    analogWrite(EnA1, 80);
    analogWrite(EnA2, 80);
    delay(100);
    s();
  } 
  else if (largest == leftV) {
    //go left
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(EnA1, 80);
    analogWrite(EnA2, 80);
    delay(100);
    s();
  } else if (largest == straightV) {
    //go straight
    s();
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
  analogWrite(EnA1, 80);
  analogWrite(EnA2, 80);
  delay(100);
}

void l() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  analogWrite(EnA1, 80);
  analogWrite(EnA2, 80);
  delay(200);
}

void s() {
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  analogWrite(EnA1, 80);
  analogWrite(EnA2, 80);
}
