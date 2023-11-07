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
int in1 = 0;
int in2 = 0;

// Initiliazing motor object
CytronMD motorR(PWM_DIR, R_PWM, R_DIR);
CytronMD motorL(PWM_DIR, L_PWM, L_DIR);

void setup() {
  // Setting up line follower pins as input
  pinMode(LFS_L, INPUT);
  pinMode(LFS_R, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  motorR.setSpeed(150);
  motorL.setSpeed(-150);

  in1 = digitalRead(LFS_L);
  in2 = digitalRead(LFS_R);

  String detect;
  
  if(in1 == 0 && in2 == 1){
    // Left sensor detecting black line
    detect = "border on left";
    // Turning right
    motorR.setSpeed(150);
    motorL.setSpeed(150);
    delay(1000);
  } 
  if(in1 == 1 && in2 == 0){
    // Right sensor detecting black line
    detect = "border on right";
    // Turning left
    motorR.setSpeed(-150);
    motorL.setSpeed(-150);
    delay(1000);
  }
  if(in1 == 0 && in2 == 0){
    // Both sensors detecting black line
    detect = "border in front";
    // reversing
    motorR.setSpeed(-150);
    motorL.setSpeed(150);
    delay(500);
    motorR.setSpeed(150);
    motorL.setSpeed(150);
    delay(1250);
  }
  if(in1 == 1 && in2 == 1) {
    detect = "no border";
    motorR.setSpeed(150);
    motorL.setSpeed(-150);
  }
  Serial.println(detect);
}
