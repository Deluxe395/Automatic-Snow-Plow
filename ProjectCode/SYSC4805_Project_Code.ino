// SYSC 4805 Project Code
// Sundar, Ryan, Ismael

#include <CytronMotorDriver.h>

// Defining Right Motor Pins
#define R_PWM 6
#define R_DIR 10

// Defining Left Motor Pins
#define L_PWM 4
#define L_DIR 8

// Line follower input 
int LFS_L = 52;
int LFS_R = 50;

// Line follower  condition variables
int line_follow_left = 0;
int line_follow_right = 0;



// Array of checker variables for each sensor
// [linefollower, IR, Ultrasonic]
int sensor_arr[3] = {0, 0, 0};

int turn_duration = 10;

void IRInterrupt(){
  // Uncomment once IR pins are set up
  // sensor_arr[1] = digitalRead(IRPIN)
}

void UltrasonicInterrupt(){
  // Uncomment when ultrasonic is setup
  //sensor_arr[3] = digitalRead(UltrasonicSensorPin)
}

void LinefollowerInterrupt(){
  if(digitalRead(52) == 1){
    sensor_arr[0] = 1;
  } else if(digitalRead(50) == 1){
    sensor_arr[0] = 2;
  }
  else{
    sensor_arr[0] = 0;
  }
}

void setup() {

  // Initiliazing motor object
  CytronMD motorR(PWM_DIR, R_PWM, R_DIR);
  CytronMD motorL(PWM_DIR, L_PWM, L_DIR);

  // Setting up line follower pins as input
  pinMode(LFS_L, INPUT);
  pinMode(LFS_R, INPUT);

//line follower interrupt  
  attachInterrupt(digitalPinToInterrupt(50), sensor[0], CHANGE);
  attachInterrupt(digitalPinToInterrupt(52), sensor[0], CHANGE);

  Serial.begin(9600);
}

void loop() {
  // 
  if (sensor_arr[0] == 0) {
    // Moving forward
    motorR.setSpeed(125);
    motorL.setSpeed(-125);
  } else if (sensor_arr[0] == 1) {
    // Border on left, Turning right
    motorR.setSpeed(200);
    motorL.setSpeed(200);
  } else if (sensor_arr[0] == 2) {
    // Border on right, Turning left
    motorR.setSpeed(-200);
    motorL.setSpeed(-200);
  } else {
    //Border in front
    for (int i = 10; i >= 0; i--) {
      // Reversing
      motorR.setSpeed(-125);
      motor.setSpeed(125);
    }

    delay(50);

  }


}