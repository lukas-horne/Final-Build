#include <SD.h>
File myFile;
const int CSPin = 10;

//temporary colour sensor alternative
bool Bool = true;

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino started");

  pinMode(CSPin, OUTPUT);
}

void loop() {
  if (/*if im in green/toxic waste*/ Bool == true) {

    // Note that even if it's not used as the CS pin, the hardware SS pin
    // (10 on most Arduino boards, 53 on the Mega) must be left as an output
    // or the SD library functions will not work.

    if (!SD.begin(CSPin)) {
      return;
    }


    // open the file for reading:
    myFile = SD.open("test.txt");

    if (myFile) {
      Serial.println("Starting file");
      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        //Serial.println(moves[i]);
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
      Serial.println("Finished file");
      // close the file:
      myFile.close();
      Bool = false;
    } else {
    }
  }
}

void left() {
  Serial.println("Left");
}

void right() {
  Serial.println("Right");
}

void forward() {
  Serial.println("Forward");
}

void backward() {
  Serial.println("Backward");
}
