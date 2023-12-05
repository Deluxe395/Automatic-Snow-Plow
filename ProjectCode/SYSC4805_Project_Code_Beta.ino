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

// Line follower input 
int LFS_L = A2;
int LFS_R = A3;

// Line follower  condition variables
int line_follow_left = 0;
int line_follow_right = 0;

// Global Handler variable for line follower 
int left_count = 0;
int right_count = 0;

// Array of checker variables for each sensor
// [linefollower, IR, Ultrasonic]
int sensor_arr[3] = {0, 0, 0};

int turn_duration = 20;
int reverse_duration = 300;

CytronMD motorR(PWM_DIR, R_PWM, R_DIR);
CytronMD motorL(PWM_DIR, L_PWM, L_DIR);

  // Setting up ultrasonic library
EZDist Ultra(TRIG, ECHO);


void IRInterrupt(){
  // Uncomment once IR pins are set up
  // sensor_arr[1] = digitalRead(IRPIN)
}

void UltrasonicHandler(float distance){
  if (distance > 6 && distance < 12){
    Serial.println(distance);
    sensor_arr[2] = 1;

  } 


}

void LinefollowerInterrupt(){
  if (analogRead(LFS_L) > 950) {
    sensor_arr[0] = 1;
  } else if (analogRead(LFS_L) > 950) {
    sensor_arr[0] = 2;
  } else {
    sensor_arr[0] = 3;
  }
}


void setup() {
  //void IRInterrupt();
 // void UltrasonicInterrupt();
  //void LinefollowerInterrupt();
  // Initiliazing motor object


  // line follower interrupt  
  attachInterrupt(LFS_L, LinefollowerInterrupt, CHANGE);
  attachInterrupt(LFS_R, LinefollowerInterrupt, CHANGE);

  // ultrasonic interrupt
  //attachInterrupt(digitalPinToInterrupt(22), UltrasonicInterrupt, CHANGE);

  Serial.begin(9600);
}

void loop() {
  // Motors Logic
  
  UltrasonicHandler(Ultra.cm());
  
  if (sensor_arr[0] == 0 && sensor_arr[2] == 0) {
    // Moving forward
    motorR.setSpeed(125);
    motorL.setSpeed(-125);
    // resetting counter variables
    turn_duration = 200;
    reverse_duration = 300;
  }

  if (sensor_arr[0] == 1) {
    // Border on left, Turning right
    Serial.println("Turning Right");
    motorR.setSpeed(20);
    motorL.setSpeed(200);
    turn_duration--;
    if(turn_duration <= 0){
      sensor_arr[0] = 0;
    }
  } else if (sensor_arr[0] == 2) {
    // Border on right, Turning left
    motorR.setSpeed(-200);
    motorL.setSpeed(-200);
    turn_duration--;
    if(turn_duration <= 0){
      sensor_arr[0] = 0;
    }
  } else {
    //Border in front
    for (int i = 10; i >= 0; i--) {
      // Reversing
      motorR.setSpeed(-125);
      motorL.setSpeed(125);
      reverse_duration--;
      if(reverse_duration <= 0){
        sensor_arr[0] = 1;
      }
    }
  }

  if (sensor_arr[2] == 1) {
    // Obstacle detected within 6cm in front
    // Stopping
    
   Serial.println("Obstacle Detected, Reversing");
    motorR.setSpeed(-125);
    motorL.setSpeed(125);
    
    if (Ultra.cm() > 12){
      reverse_duration -= 1;
    }

    
    Serial.println(reverse_duration);
  
    if(reverse_duration <= 0){
      sensor_arr[0] = 1;
      sensor_arr[2] = 0;
    }
  }

  delay(100);
}




