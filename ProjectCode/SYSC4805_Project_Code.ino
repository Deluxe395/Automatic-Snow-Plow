// SYSC 4805 Project Code
// Sundar, Ryan, Ismael

#include <CytronMotorDriver.h>
#include <EZDist.h>

// Defining Right Motor Pins
#define R_PWM 6
#define R_DIR 10

// Defining Left Motor Pins
#define L_PWM 4
#define L_DIR 8

// Defining Ultrasonic variables
#define TRIG 24
#define ECHO 22

// IR variables
#define IR_L 28
#define IR_R 30

// IR input
int IR_L_input = 0;
int IR_R_input = 0;

// Line follower input 
int LFS_L = A2;
int LFS_R = A3;

// Initiliazing motor object
CytronMD motorR(PWM_DIR, R_PWM, R_DIR);
CytronMD motorL(PWM_DIR, L_PWM, L_DIR);

// Setting up ultrasonic library
EZDist Ultra(TRIG, ECHO);

void setup() {
  
  pinMode(IR_L, INPUT);
  pinMode(IR_R, INPUT);

  Serial.begin(9600);
}

void loop() {

  // Moving Forward
  Serial.println("Moving Forward");
  motorR.setSpeed(100);
  motorL.setSpeed(-100);

  if ((analogRead(LFS_L) >= 950 && analogRead(LFS_R) <= 950)){
    // Turning right
    motorR.setSpeed(-100);
    motorL.setSpeed(100);

    delay(600);

    Serial.println("Turning Right");
    motorR.setSpeed(125);
    motorL.setSpeed(125);

    delay(random(1000, 1500));
  }

  if (analogRead(LFS_R) >= 950 && analogRead(LFS_L) <= 950){
    // Turning Left
    motorR.setSpeed(-100);
    motorL.setSpeed(100);

    delay(600);

    Serial.println("Turning Left");
    motorR.setSpeed(-125);
    motorL.setSpeed(-125);

    delay(random(1000, 2000));
  }

  if (analogRead(LFS_R) >= 950 && analogRead(LFS_L) >= 950){
    // Reversing
    Serial.println("Reversing");
    motorR.setSpeed(-100);
    motorL.setSpeed(100);

    delay(600);

    motorR.setSpeed(-125);
    motorL.setSpeed(-125);

    delay(random(1000, 2000));
  }

  // Ultrasonic Sensor

  int distance = Ultra.cm();

  if(distance >= 6 && distance <= 12) {
    // Reversing
    Serial.println(distance);
    Serial.println("Object detected");
    motorR.setSpeed(-100);
    motorL.setSpeed(100);

    delay(600);

    Serial.println("Turning left");
    motorR.setSpeed(-125);
    motorL.setSpeed(-125);

    delay(random(1000, 2000));
  }

   // IR sensor

  IR_L_input = digitalRead(IR_L);
  IR_R_input = digitalRead(IR_R);

  Serial.println(IR_L_input);
  Serial.println(IR_R_input);

  if (IR_L_input == 0 && IR_R_input == 1){
    delay(30);
    IR_L_input = digitalRead(IR_L);
    IR_R_input = digitalRead(IR_R);

    if (IR_L_input == 0 && IR_R_input == 1){
      // Turning right
      motorR.setSpeed(-100);
      motorL.setSpeed(100);

      delay(500);

      Serial.println("IR turn right");
      motorR.setSpeed(125);
      motorL.setSpeed(125);

      delay(random(500, 1000));
    }
  }

  if (IR_L_input == 1 && IR_R_input == 0){
    delay(30);
    IR_L_input = digitalRead(IR_L);
    IR_R_input = digitalRead(IR_R);

    if(IR_L_input == 1 && IR_R_input == 0){
      // Turning Left
      motorR.setSpeed(-100);
      motorL.setSpeed(100);

      delay(500);

      Serial.println("IR turn left");
      motorR.setSpeed(-125);
      motorL.setSpeed(-125);

      delay(random(500, 1000));
    }
  }

  if (IR_L_input == 0 && IR_R_input == 0) {
    delay(30);
    IR_L_input = digitalRead(IR_L);
    IR_R_input = digitalRead(IR_R);

    if (IR_L_input == 0 && IR_R_input == 0){
      // Reversing
      Serial.println("IR object in front");
      motorR.setSpeed(-100);
      motorL.setSpeed(100);

      delay(500);

      Serial.println("Turning Left");
      motorR.setSpeed(-125);
      motorL.setSpeed(-125);

      delay(random(500, 1000));
    }
  }

  delay(50);

}
