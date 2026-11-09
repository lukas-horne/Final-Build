String test = "LLRRFFBB";
char moves[64];

void setup() {
 Serial.begin(9600);
 test.toCharArray(moves, test.length());

for (int i =0; i < test.length(); i++){
   //Serial.println(moves[i]);
 switch(moves[i]){
   case 'L':
     left();
		break;
   case 'R':
     right();
		break;
   case 'F';
     forward();
   break;
   case 'B';
   backward();
   break;
 }
}
}

void left(){
 Serial.println("Left move");
}

void right(){
 Serial.println("Right move");
}

void forward(){
 Serial.println("Forward move");
}

void backward(){
 Serial.println("Backward move");
}
