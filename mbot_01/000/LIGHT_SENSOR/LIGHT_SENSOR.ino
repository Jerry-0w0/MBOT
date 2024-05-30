#define MR A0
#define RR A1
#define ML A2
#define MM A3
#define LL A4
int sensorValue;

void setup() {
  Serial.begin(9600); // 初始化串口通信
  pinMode(13,1);
}

void loop() {
  //sensorValue = analogRead(A6); // light_sensor
  sensorValue = analogRead(A7);//button
  digitalWrite(13,255);
  //sensorValue = analogRead(MR);
  //sensorValue = analogRead(RR);
  //sensorValue = analogRead(ML);
  //sensorValue = analogRead(MM);
  //sensorValue = analogRead(LL);
  Serial.println(sensorValue); // 将读取的数值发送到串口监视器
  delay(1000); // 等待一段时间再继续下一次读取
  digitalWrite(13,0);
  delay(1000);
}
