// 가변 저항을 이용하여 RGB led를 제어하는 code
const int VResistor = A0;
const int led[3] = {9, 10, 11};

void setup(){
  for (int i =0; i <3; i++){
    pinMode(led[i], OUTPUT);
  }
}

void loop(){
  int value = analogRead(VResistor);
  
  if(value >= 256){
    digitalWrite(led[0], HIGH);
  }
  else{
    digitalWrite(led[0], LOW);
  }
  
  if(value >= 512){
    digitalWrite(led[1], HIGH);
  }
  else{
    digitalWrite(led[1], LOW);
  }
  
  if(value >= 768){
    digitalWrite(led[2], HIGH);
  }
  else{
    digitalWrite(led[2], LOW);
  }
}

    
  