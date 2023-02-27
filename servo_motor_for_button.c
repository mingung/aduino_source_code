//서보 모터 제어

#include <Servo.h>

const int servoPin = 10;
const int yellowPin = 5;
const int redPin = 6;
const int greenPin = 7;
int angle = 0;
Servo myservo;

void setup()
{
  myservo.attach(servoPin);
  myservo.write(0);
  
  pinMode(yellowPin, INPUT);
  pinMode(redPin, INPUT);
  pinMode(greenPin, INPUT);

}

void loop()
{
  if(digitalRead(yellowPin) == HIGH){
    angle = 0;
    myservo.write(angle);
  }
  else if(digitalRead(redPin) == HIGH){
    angle = 90;
    myservo.write(angle);
  }
  else if(digitalRead(greenPin) == HIGH){
    angle = 180;
    myservo.write(angle);
  }
}