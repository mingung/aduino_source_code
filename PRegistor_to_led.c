const int PRegistor = A0;
const int led = 9;

void setup(){
}

void loop(){
  int value = analogRead(PRegistor);
  analogWrite(led, value/4);
}
