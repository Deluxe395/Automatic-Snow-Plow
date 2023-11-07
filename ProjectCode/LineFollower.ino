int LFS_L = 52;
int LFS_R = 50;

int in1 = 0;
int in2 = 0;



void setup() {
  // put your setup code here, to run once:
  pinMode(LFS_L, INPUT);
  pinMode(LFS_R, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  in1 = digitalRead(LFS_L);
  in2 = digitalRead(LFS_R);

  String left;
  String right;

  if(in1 == 1){
    left = 'B';
  } else{
    left = 'W';
  }

  if(in2 == 1){
    right = 'B';
  } else{
    right = 'W';
  }


  Serial.println("L1, Group 6 >> Left: " + left +  " Right: " + right);
  Serial.println(String(in1));
  Serial.println(String(in2));
  delay(500);
}
