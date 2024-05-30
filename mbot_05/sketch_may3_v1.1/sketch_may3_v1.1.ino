
#define ECHOPIN 12
#define M1_left 4
#define M2_right 7
#define M1_PWM 6
#define M2_PWM 5
#define butPin A7
#define MR A0
#define RR A1
#define ML A2
#define MM A3
#define LL A4
byte butLst;
byte but;
int  butCnt = 0;
float dist;
unsigned long msec;
void setup() {
  Serial.begin(9600);
  pinMode(M1_left, OUTPUT);
  pinMode(M2_right, OUTPUT);
  pinMode(ECHOPIN,INPUT);
  pinMode(13, OUTPUT);
   butLst = digitalRead (butPin);
  pinMode(butPin, INPUT_PULLUP);
  motor(0,0);

}
void scan_dist(){
  digitalWrite(ECHOPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ECHOPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ECHOPIN, LOW);
  dist = pulseIn(ECHOPIN, HIGH) / 58.2; // 公分
  dist = 1.0617 * dist - 4.2649; //實際距離
  Serial.println(dist);
}
void block(){
    scan_dist();
    if(dist < 15){
      motor(100, -100);
      delay(50);
      motor(0, 0);/*
      motor(100, -100);
      delay(400);
      motor(200, 100);
      delay(1000);
      motor(0, 0);*/
    }
  
}
void loop() {
  
  but  = analogRead(butPin);
  if (butLst != but)  {
    butLst = but;
    if (LOW == but) {   // button pressed
      butCnt++;
      delay(10);
      if (1 == butCnt) motor(250, 250), block();
    }
  }
  
  /*int val = digitalRead(12); 
  Serial.println(val);
  delay(1000);*/
  // s = 340 m/s × t / 2.

}

void motor(int a, int b){//speed_check
  if (a >= 0) {
    digitalWrite(M1_left,1);
  } 
  else {
    a = -(a);
    digitalWrite(M1_left,0);
  }
  if (b >= 0) {
    digitalWrite(M2_right,0);
  } 
  else {
    b = -(b);
    digitalWrite(M2_right,1);
  }
  if (a > 250)  a = 250;
  if (b > 250)  b = 250;
  analogWrite(M1_PWM, a);
  analogWrite(M2_PWM, b);
}
