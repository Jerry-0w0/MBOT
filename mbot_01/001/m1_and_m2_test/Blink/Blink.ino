#define M1_left 4
#define M2_right 7
#define M1_PWM 6
#define M2_PWM 5
#define butPin A7

byte butLst;
byte but;

int  butCnt = 0;
int M1_speed, M2_speed;
unsigned long msec;
unsigned long butMsec;
unsigned long ledMsec;

void setup() {
  pinMode(M1_left, OUTPUT);
  pinMode(M2_right, OUTPUT);
  digitalWrite(M1_left,1);
  digitalWrite(M2_right,0);
  pinMode(butPin, INPUT_PULLUP);
  butLst = digitalRead (butPin);
} 

void checkbotton(void)
{  
  butCnt++;
  if (msec - butMsec < 500 && 2 <= butCnt)  {
    motor();
  }
  butMsec = msec;
    delay(30);         // debounce
}


void loop(void){
  msec = millis ();
  but  = analogRead(butPin);;
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
void motor(){
  delay(1000);
  M1_speed = -255;
  M2_speed = -60;
  speed_check();
//  analogWrite(M1_PWM, -1);//left
// analogWrite(M2_PWM, 246);//right  
}
//M2 = M1 - 7.7273
void speed_check(){
  if(M1_speed > 255){
      analogWrite(M1_PWM, 255);
    }
    else if(M1_speed < 0){
      digitalWrite(M1_left,0);
      analogWrite(M1_PWM, abs(M1_speed));
    }
    else{
      analogWrite(M1_PWM, M1_speed); 
    }

    if(M2_speed > 255){
      analogWrite(M2_PWM, 255);
    }
    else if(M2_speed < 0){
      digitalWrite(M2_right,1);
      analogWrite(M2_PWM, abs(M2_speed));
    }
    else{
      analogWrite(M2_PWM, M2_speed); 
    }

}
