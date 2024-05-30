
#define ECHOPIN 12
void setup() {
  Serial.begin(9600);
  pinMode(ECHOPIN,INPUT);
}

void loop() {
  digitalWrite(ECHOPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ECHOPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ECHOPIN, LOW);

  double dist = pulseIn(ECHOPIN, HIGH) / 58.2; // 公分
  Serial.println(dist);
  delay(100);
  /*int val = digitalRead(12); 
  Serial.println(val);
  delay(1000);*/
  // s = 340 m/s × t / 2.

}
