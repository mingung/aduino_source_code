// C++ code
// to RGB on/off light
void setup()
{
   pinMode(9, OUTPUT); 
   pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);

}

void loop()
{
  analogWrite(9, 255); // full red light 
  analogWrite(10, 0); // green light off
  analogWrite(11, 0); // blue light off
  delay(2000); // delay 2s (눈에 보이게)
  
  analogWrite(9, 0);
  analogWrite(10, 255);
  analogWrite(11, 0);
  delay(2000); // delay 2s (눈에 보이게)

  
  analogWrite(9, 0);
  analogWrite(10, 0);
  analogWrite(11, 255);
  delay(2000); // delay 2s (눈에 보이게)




}