// 가변저항을 이용한 led 밝기 제어
const int VResistor = A0;
const int led = 9;

void setup(){
}

void loop(){
  
  int value = analogRead(VResistor); //읽어온 아날로그 핀의 값을 value값에 저장
  int lightValue = value/4; //가변저항 값 (0~1023), 4로 나누어서 led 밝기 (0~255)로 맞춰줌
  analogWrite(led, lightValue);
}