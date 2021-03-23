//ARDUINO LINE FOLLOWING CAR//
 
//including the libraries
#include <AFMotor.h>

//defining pins and variables
#define left A0
#define right A1

//defining motors
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

bool detectBoth = false;
int bothCounter = 0;



void setup() {
  //declaring pin types
  pinMode(left,INPUT);
  pinMode(right,INPUT);
  //begin serial communication
  Serial.begin(9600);
  
}

void moveStraight() {
  motor1.run(FORWARD);
  motor1.setSpeed(150);
  motor2.run(FORWARD);
  motor2.setSpeed(150);
  motor3.run(FORWARD);
  motor3.setSpeed(150);
  motor4.run(FORWARD);
  motor4.setSpeed(150);
}

void moveLeft() {
   motor1.run(FORWARD);
   motor1.setSpeed(200);
   motor2.run(FORWARD);
   motor2.setSpeed(200);
   motor3.run(BACKWARD);
   motor3.setSpeed(200);
   motor4.run(BACKWARD);
   motor4.setSpeed(200);
}

void moveRight() {
  motor1.run(BACKWARD);
  motor1.setSpeed(200);
  motor2.run(BACKWARD);
  motor2.setSpeed(200);
  motor3.run(FORWARD);
  motor3.setSpeed(200);
  motor4.run(FORWARD);
  motor4.setSpeed(200);
}

void dontMove() {
  motor1.run(RELEASE);
  motor1.setSpeed(0);
  motor2.run(RELEASE);
  motor2.setSpeed(0);
  motor3.run(RELEASE);
  motor3.setSpeed(0);
  motor4.run(RELEASE);
  motor4.setSpeed(0);
}

void loop(){
  //printing values of the sensors to the serial monitor
  Serial.println("Left Reading:"  + digitalRead(left));
  
  Serial.println("Right Reading:" + digitalRead(right));

  //line detected by both
  if(digitalRead(left)==0 && digitalRead(right)==0){
    //Forward
    moveStraight();

    detectBoth = true;
  }
  //line detected by left sensor
  else if(digitalRead(left)==0 && !digitalRead(right)==0){
    //turn left
    moveLeft();

    if (detectBoth) {
      bothCounter++;
      detectBoth = false;
    }
    
  }
  //line detected by right sensor
  else if(!digitalRead(left)==0 && digitalRead(right)==0){
    //turn right
    moveRight();

    if (detectBoth) {
      bothCounter++;
      detectBoth = false;
    }
  }
  //line detected by none
  else if(!digitalRead(left)==0 && !digitalRead(right)==0){
    //stop
    dontMove();
   
  }
  
}
