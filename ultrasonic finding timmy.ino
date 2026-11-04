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

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  // Variables for duration of ping and the distance in cm
  long duration, cm;

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
}

long microsecondsToCentimetres(long microseconds) {
  return microseconds / 29 / 2;
}


int right() {
  // turn right
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  analogWrite(EnA1, 80);
  analogWrite(EnA2, 80);
  delay(300);
  int distance = cm;
  delay(5000);
  return distance;
}

int left() {
  // turn left
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  analogWrite(EnA1, 80);
  analogWrite(EnA2, 80);
  delay(300);
  int distance = cm;
  delay(5000);
  return distance;
}

int straight() {
  //read straight
  delay(300);
  int distance = cm;
  delay(5000);
  return distance;
}
