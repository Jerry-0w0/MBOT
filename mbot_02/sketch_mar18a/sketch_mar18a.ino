#define MR A0
#define RR A1
#define ML A2
#define MM A3
#define LL A4

float analogRR, analogMR, analogMM, analogML, analogLL; // Renamed variables to avoid conflicts
float RRmin , MRmin, MMmin, MLmin, LLmin, RRmax, MRmax, MMmax, MLmax, LLmax;

void setup() {
  Serial.begin(9600);
}

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
  Serial.print("Variablemin:");
  Serial.println(MMmin);
  Serial.print("Variablemax:");
  Serial.println(MMmax);
  //==========================
  float normRR = (analogRR - RRmin) / (RRmax - RRmin);
  float normMR = (analogMR - MRmin) / (MRmax - MRmin);
  float normMM = (analogMM - MMmin) / (MMmax - MMmin);
  float normML = (analogML - MLmin) / (MLmax - MLmin);
  float normLL = (analogLL - LLmin) / (LLmax - LLmin);
  Serial.print("norm_MR:");
  Serial.println(normMR);
  Serial.print("norm_RR:");
  Serial.println(normRR);
  Serial.print("norm_MM:");
  Serial.println(normMM);
  Serial.print("norm_ML:");
  Serial.println(normML);
  Serial.print("norm_LL:");
  Serial.println(normLL);
  delay(1000);
}


