const int activeB = 10;
void setup()
{
  pinMode(activeB, OUTPUT);
  
  for(int i=0; i<3; i++){
    digitalWrite(activeB, HIGH);
    delay(2000);
    digitalWrite(activeB, LOW);
    delay(2000);
  }
  
}

void loop()
{

}