
int red = 9;
int green = 10;
int blue = 11;

void setup()
{
   Serial.begin(115200);
   pinMode(red, OUTPUT); 
   pinMode(green, OUTPUT);
   pinMode(blue, OUTPUT);

}

void loop()
{
  if(Serial.available()){
    int rValue = Serial.parseInt();
    int gValue = Serial.parseInt();
    int bValue = Serial.parseInt();
    
    if(Serial.read() == '\n'){
      analogWrite(red, rValue);
      analogWrite(green, gValue);
      analogWrite(blue, bValue);
    }
  }
}