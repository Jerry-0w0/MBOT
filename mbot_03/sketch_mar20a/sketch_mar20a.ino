#define M1_left 4
#define M2_right 7
#define M1_PWM 6
#define M2_PWM 5
#define MR A0
#define RR A1
#define ML A2
#define MM A3
#define LL A4

float analogRR, analogMR, analogMM, analogML, analogLL, M1, M2; // Renamed variables to avoid conflicts
float RRmin , MRmin, MMmin, MLmin, LLmin, RRmax, MRmax, MMmax, MLmax, LLmax;
float RR_value, MR_value, MM_value, ML_value, LL_value;


void setup() {
  Serial.begin(9600);
} 

//M2=1.0641M1-24.419






void loop() {

  analogMR = analogRead(MR); // Updated analog readings to separate variables
  analogRR = analogRead(RR);
  analogMM = analogRead(MM);
  analogML = analogRead(ML);
  analogLL = analogRead(LL);
  // Update Xmax
  if (RRmax < analogRR) {
    RRmax = analogRR;
  }
  if (MRmax < analogMR) {
    MRmax = analogMR;
  }
  if (MMmax < analogMM) {
    MMmax = analogMM;
  }
  if (MLmax < analogML) {
    MLmax = analogML;
  }
  if (LLmax < analogLL) {
    LLmax = analogLL;
  }

  // Update Xmin
  if (RRmin > analogRR) {
    RRmin = analogRR;
  }
  if (MRmin > analogMR) {
    MRmin = analogMR;
  }
  if (MMmin > analogMM) {
    MMmin = analogMM;
  }
  if (MLmin > analogML) {
    MLmin = analogML;
  }
  if (LLmin > analogLL) {
    LLmin = analogLL;
  }
  /*
  Serial.print("Variablemin:");
  Serial.println(MMmin);
  Serial.print("Variablemax:");
  Serial.println(MMmax);*/
  //===================================
  float normRR = (analogRR - RRmin) / (RRmax - RRmin);
  float normMR = (analogMR - MRmin) / (MRmax - MRmin);
  float normMM = (analogMM - MMmin) / (MMmax - MMmin);
  float normML = (analogML - MLmin) / (MLmax - MLmin);
  float normLL = (analogLL - LLmin) / (LLmax - LLmin);
  float sum = normLL * -2.4 + normML * -1.2 + normMM * 0.5 + normMR * 1.2 + normRR * 2.4;

  //Serial.print("RR_value:");
  Serial.print(normLL);
  Serial.print("  ");
  //Serial.print("MR_value:");
  Serial.print(normML);
  Serial.print("  ");  
  //Serial.print("MM_value:");
  Serial.print(normMM);
  Serial.print("  ");
  //Serial.print("ML_value:");
  Serial.print(normMR);
  Serial.print("  ");
  //Serial.print("LL_value:");
  Serial.print(normRR);
  Serial.print("  ");
  Serial.println(sum);
  //=====================================
  
  delay(100);
}


