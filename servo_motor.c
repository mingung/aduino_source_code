//서보 모터 제어

#include <Servo.h>

const int servoPin = 10;
Servo myservo;

void setup()
{
  myservo.attach(servoPin);
  myservo.write(0);
  
  delay(1000);
}

void loop()
{
  for(int i =0; i<=3; i++){
    myservo.write(180);
    delay(1000);
    myservo.write(0);
    delay(1000);
  }
}