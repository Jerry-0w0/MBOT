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
#define ECHOPIN 12
char turn;
float M1_speed, M2_speed, Pt, Kp, Ki, Kd, Turn, integral, derivative, lastError, Weighted, error;
float normIR[] = {0, 0, 0, 0, 0}; 
float sum, dist;
float IRmax[]= {analogRead(LL), analogRead(ML), analogRead(MM), analogRead(MR), analogRead(RR)}; 
float IRmin[]= {analogRead(LL), analogRead(ML), analogRead(MM), analogRead(MR), analogRead(RR)};
float IR[]= {analogRead(LL), analogRead(ML), analogRead(MM), analogRead(MR), analogRead(RR)};
byte butLst;
byte but;
int  butCnt = 0;
unsigned long msec;
unsigned long IRMsec;
//================setup=================================================================================================================================
void setup() {
  Serial.begin(9600);
  pinMode(M1_left, OUTPUT);
  pinMode(M2_right, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(butPin, INPUT_PULLUP);
  butLst = digitalRead (butPin);
  integral = 0;
  lastError = 0;
} 
//================setup==============================================================================================================================
//================scan_dist==============================================================================================================================
void scan_dist(){
  digitalWrite(ECHOPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ECHOPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ECHOPIN, LOW);
  dist = pulseIn(ECHOPIN, HIGH) / 58.2; // 公分
  dist = 1.0617 * dist - 4.2649; //實際距離
  //Serial.println(dist);
}
//================scan_dist==============================================================================================================================

//=============motor=================================================================================================================================
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
//===============sharp_Rturn=================================================================================================================
//=========PID===============================================================================================================================
void PID(int Kp, int Ki, int Kd,int Pt){
  while(1){
    scan_dist();
    scanIR();
      if(sum == 0 ){
        if(turn != 's'){
          motor(0, 0);
          (turn == 'r') ? motor(0, 250) : motor(250, 0);
          //delay(30);
          while(!IR[2]) scanIR();
            turn = 'r';
        }
      }
    if(sum > 2 ){
      if(turn != 's'){
        motor(0, 0);
        (turn == 'r') ? motor(0, 250) : motor(250, 0);
        delay(10);
        while(!IR[2]) scanIR();
          turn = 'r';
      }
    }
    if(IR[4] && !IR[0]) turn = 'l';
    if(IR[0] && !IR[4]) turn = 'r';
    Weighted = normIR[0] * -1.2 + normIR[1] * -0.8 + normIR[2] * 0.2 + normIR[3] * 0.8 + normIR[4] * 1.2;
    if((Weighted < 3) && (Weighted > -3)) error = 2.5594 * Weighted ;//
    integral = integral + error;
    derivative = error - lastError;
    Turn = Kp * error + Ki * integral + Kd * derivative;
    M1_speed = Pt + Turn - abs(error) * 13;//7
    M2_speed = Pt - 8 - Turn - abs(error) * 13;//7
      if(!IR[1] && IR[2] && !IR[3] ){
        M1_speed = M1_speed * 1.2, M2_speed = M2_speed * 1.2;
        integral = 0;
      }
    motor(abs(M1_speed), abs(M2_speed));
    lastError = error;
    if(sum == 5){
      delay(10);
      while(sum == 5){
        motor(0, 0);
      }
    }
    if(dist < 15){
      block();

    }
  }
  
}
    
    
//=========PID===============================================================================================================================
void block(){
  motor(0, 0);
  delay(40);
  motor(-100, 100);
  delay(380);
  motor(180, 180);
  delay(450);
  motor(100, -100);
  delay(530);
  motor(180, 180);
  scanIR();
  while(!IR[2]) scanIR();

}
//============scanIR=====================================================================================================================================
void scanIR(){
  sum = 0;
  IR[0]= analogRead(LL);
  IR[1]= analogRead(ML);
  IR[2]= analogRead(MM);
  IR[3]= analogRead(MR);
  IR[4]= analogRead(RR);
  for(int i=0; i<5; i++){
      normIR[i] = (IR[i] - IRmin[i]) / (IRmax[i] - IRmin[i]);
      (IR[i] > (IRmax[i]-IRmin[i])/2) ? IR[i] = 1 : IR[i] = 0;
      sum += IR[i];
      //Serial.println(normIR[i]);
    }
}
//============scanIR=====================================================================================================================================


//==============MAIN=======================================================================================================================================
void loop(void){
  motor(0,0);
  but  = analogRead(butPin);
  if (butLst != but)  {
    butLst = but;
    if (LOW == but) {   // button pressed
      butCnt++;
      delay(10);
      if (1 == butCnt)  motor_circles();
    }
  }
  
  
    //Serial.println(butCnt);
  if(butCnt > 1){
    scanIR();
    PID(44, 0.8, 42, 180);//PID(46, 0.8, 40, 180);
  }
}
//==============MAIN======================================================================================================================================


//========spin around in circles=========================================================================================================================
float Compare_max(float max, float ir){
  if (max < ir) max = ir;
  return max;
}

float Compare_min(float min, float ir){
 if (min > ir) min = ir;
  return min;
}

void motor_circles(){
  msec = millis ();
  IRMsec = msec;
  IRmax[0]= analogRead(LL);
  IRmax[1]= analogRead(ML);
  IRmax[2]= analogRead(MM);
  IRmax[3]= analogRead(MR);
  IRmax[4]= analogRead(RR);
  IRmin[0]= analogRead(LL);
  IRmin[1]= analogRead(ML);
  IRmin[2]= analogRead(MM);
  IRmin[3]= analogRead(MR);
  IRmin[4]= analogRead(RR);
  while(IRMsec - msec < 1000)  {
    float IR[]= {analogRead(LL), analogRead(ML), analogRead(MM), analogRead(MR), analogRead(RR)}; 
     for(int i=0; i<5; i++){
      IRmax[i] = Compare_max(IRmax[i], IR[i]);
      IRmin[i] = Compare_min(IRmin[i], IR[i]);
    }
    motor(200, -200);
    IRMsec = millis();
  }
  motor(0,0);
  delay(1000);
}
//========spin around in circles=========================================================================================================================

