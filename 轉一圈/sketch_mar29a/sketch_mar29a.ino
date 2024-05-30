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
float M1_speed, M2_speed;
//========butcheck==========
byte butLst;
byte but;

int  butCnt = 0;

unsigned long msec;
unsigned long butMsec;
unsigned long IRMsec;



void checkbotton(void)
{  
  butCnt++;
  if (msec - butMsec < 500 && 2 <= butCnt)  {
    motor_circles();
  }
  butMsec = msec;
    delay(30);         // debounce
}
//========butcheck==========

void setup() {
  Serial.begin(9600);
  pinMode(M1_left, OUTPUT);
  pinMode(M2_right, OUTPUT);
  pinMode(butPin, INPUT_PULLUP);
  butLst = digitalRead (butPin);
} 

void loop(void){
  msec = millis ();
  but  = analogRead(butPin);
      if (butLst != but)  {
        butLst = but;
         if (LOW == but) {   // button pressed
         checkbotton();
         }
      }
  if (1 < butCnt){
    butCnt  = 0;
  }
}
//spin around in circles
float Compare_max(float max, float ir){
  if (max < ir) {
    max = ir;
  }
  return max;
}

float Compare_min(float min, float ir){
 if (min > ir) {
    min = ir;
  }
  return min;
}

void motor_circles(){
  delay(1000);
  msec = millis ();
  IRMsec = msec;
  float IRmax[5]; 
  float IRmin[5];
  float normIR[] = {0, 0, 0, 0, 0}; 
  while(IRMsec - msec < 1900)  {


    float IR[]= {analogRead(LL), analogRead(ML), analogRead(MM), analogRead(MR), analogRead(RR)};
    for(int i=0; i<5; i++){
      IRmax[i] = Compare_max(IRmax[i], IR[i]);
      IRmin[i] = Compare_min(IRmin[i], IR[i]);
      normIR[i] = (IR[i] - IRmin[i]) / (IRmax[i] - IRmin[i]);
      Serial.print(IRmax[i]);
      Serial.print("  ");
      Serial.print(IRmin[i]);
      Serial.print("  ");
      Serial.print(normIR[i]);
      Serial.print("  ");
    }
    Serial.println("  ");
    digitalWrite(M1_left,1);
    digitalWrite(M2_right,1);
    M1_speed = 100;
    M2_speed = 108;
    analogWrite(M1_PWM, M2_speed);//left
    analogWrite(M2_PWM, M1_speed);//right
    IRMsec = millis();
  }
  digitalWrite(M1_left,1);
  digitalWrite(M2_right,0);
  M1_speed = 0;
  M2_speed = 0;
  analogWrite(M1_PWM, M2_speed);//left
  analogWrite(M2_PWM, M1_speed);//right  
}
//M2 = M1 - 7.7273
