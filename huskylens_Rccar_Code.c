//The DIY Life
//Michael Klements
//16/04/2021
//Huskylens Line Tracking Robot
//Adapted from Huskylens Line Tracking example by By [Angelo qiao](Angelo.qiao@dfrobot.com)

#include "HUSKYLENS.h" // 허스키렌즈 라이브러리                          
#include "SoftwareSerial.h" // 디지털 핀을 시리얼 포트로 사용 
#include "PIDLoop.h" // PID 제어 라이브러리
#include <AFMotor.h> // L293D 라이브러리

AF_DCMotor LeftFront(1); // LeftFront Motor 객체                         
AF_DCMotor LeftBack(2);  // LeftBack Motor 객체 
AF_DCMotor RightBack(3);  // RightBack Motor 객체 
AF_DCMotor RightFront(4);  // RightFront Motor 객체 

byte motorSpeed = 150;                             // 최대 모터 스피드(최소 모터 150 정도로 하면 될듯)
int motorOffset = 15;                             // 한 쪽이 더 강력해지는 요인 
int turnSpeed = 50;                               // 회전시 모터 속도에 추가될 양
int leftSpeed = 0;                             
int rightSpeed = 0;                               // 좌우 모터 속도를 유지하기 위한 변수

PIDLoop headingLoop(120, 0, 0, false);            // heading을 위한 PID 컨트롤 시스템, P만 사용
HUSKYLENS huskylens;                              // 허스키렌즈 객체 선언
int ID1 = 1;                                      // ID1 선언
int ID2 = 2;                                      // ID2 선언
int ID3 = 3;                                      // ID3 선언

void printResult(HUSKYLENSResult result);	

void setup() 
{
  Serial.begin(115200);                                         // 시리얼 통신 속도
  Wire.begin();                                                 // 통신 라이브러리
  while (!huskylens.begin(Wire))                                // 통신 신호를 아두이노에서 받아들임
  {
      Serial.println(F("Begin failed!")); // 연결이 되지 않음
      Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protol Type>>I2C)")); 		// 허스키렌즈의 세팅값을 확인하세요
      Serial.println(F("2.Please recheck the connection.")); // 연결을 다시 확인하세요
      delay(100);
  }
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);            // 라인 트래킹 알고리즘 넣기
  LeftFront.setSpeed(200);                                        
  LeftBack.setSpeed(200);
  RightBack.setSpeed(200);
  RightFront.setSpeed(200);							                          // 4개의 DC모터 초기 스피드 0으로 설정
  GoForward();                                                  // 모터 가동
  //accelerate();                                                 // 모터 가속

} 

void loop() 
{

  while(1)
  {
    tracking_ID1();
    if(huskylens.available(ID2))
    {
      trackingStop_ID1();
      break;
    }
  }

  while(1)
  {
    tracking_ID2();
    if(huskylens.available(ID1))
    {
      break;
    }
  }
 
  
   
}

void accelerate()                                 // 정지상태에서 최대속도까지 가속하는 함수
{
  for (int i=0; i<motorSpeed; i++)                // 0부터 motorSpeed까지 함수 반복
  {
    RightBack.setSpeed(i);                        // 모터 회전을 유지하면서 점점 가속하도록 설정 
    RightFront.setSpeed(i);
    LeftFront.setSpeed(i+motorOffset);
    LeftBack.setSpeed(i+motorOffset);
    delay(10);
  }
}

void decelerate()                                 // 최대속도에서 정지상태로 감속하는 함수
{
  for (int i=motorSpeed; i!=0; i--)               // motorSpeed부터 0까지 함수 반복
  {
    RightBack.setSpeed(i);                        // 모터 회전 유지하면서 점점 감속하도록 설정 
    RightFront.setSpeed(i);
    LeftFront.setSpeed(i+motorOffset);
    LeftBack.setSpeed(i+motorOffset); 
    delay(10);
  }
}

void GoForward()                                // 모튼 모터가 정방향 회전
{
  LeftFront.run(FORWARD);                                        
  LeftBack.run(FORWARD);
  RightBack.run(FORWARD);
  RightFront.run(FORWARD);		
}

void stop()                                   // 모든 모터가 정지
{
  LeftFront.run(RELEASE);                                        
  LeftBack.run(RELEASE);
  RightBack.run(RELEASE);
  RightFront.run(RELEASE);	
}

void turnLeft(int duration)                                 // 좌회전시 모터 제어 함수
{
  RightBack.setSpeed(motorSpeed+turnSpeed);                 //Set the motors to the motor speed
  RightFront.setSpeed(motorSpeed+turnSpeed);
  LeftFront.setSpeed(motorSpeed+motorOffset+turnSpeed);
  LeftBack.setSpeed(motorSpeed+motorOffset+turnSpeed);
  RightBack.run(FORWARD);
  RightFront.run(FORWARD);
  LeftFront.run(BACKWARD);
  LeftBack.run(BACKWARD);
  delay(duration);
  RightBack.setSpeed(motorSpeed);                           //Set the motors to the motor speed
  RightFront.setSpeed(motorSpeed);
  LeftFront.setSpeed(motorSpeed+motorOffset);
  LeftBack.setSpeed(motorSpeed+motorOffset);
  GoForward();
}

void turnRight(int duration)                                // 우회전시 모터 제어 함수
{
  RightBack.setSpeed(motorSpeed+turnSpeed);                 //Set the motors to the motor speed
  RightFront.setSpeed(motorSpeed+turnSpeed);
  LeftFront.setSpeed(motorSpeed+motorOffset+turnSpeed);
  LeftBack.setSpeed(motorSpeed+motorOffset+turnSpeed);
  RightBack.run(BACKWARD);
  RightFront.run(BACKWARD);
  LeftFront.run(FORWARD);
  LeftBack.run(FORWARD);
  delay(duration);
  RightBack.setSpeed(motorSpeed);                           //Set the motors to the motor speed
  RightFront.setSpeed(motorSpeed);
  LeftFront.setSpeed(motorSpeed+motorOffset);
  LeftBack.setSpeed(motorSpeed+motorOffset);
  GoForward();
}

void tracking_ID1()                                             // ID1 tracking function
{
  int32_t error;
  if (!huskylens.request(ID1))                                  // 연결이 안됐을 때
  {
    Serial.println(F("Check connection to Huskeylens"));
    leftSpeed = 0; 
    rightSpeed = 0;
  }
  else if(!huskylens.isLearned())                               // 학습이 안됐을 때
  {
    Serial.println(F("No object has been learned"));
    leftSpeed = 0; 
    rightSpeed = 0;
  }
  else if(!huskylens.available())                               // 스크린에 화살표가 표시되지 않은 경우
  {  Serial.println(F("No arrow on the screen yet"));
    leftSpeed = 0; 
    rightSpeed = 0;
  }	
  else                                                          // 선이 감지되고 화면에 표시 될때
  {
    HUSKYLENSResult result = huskylens.read();                  // 읽고 결과를 표시한다
    printResult(result);
    
    error = (int32_t)result.xTarget - (int32_t)160;             // 트래킹 에러 계산
    headingLoop.update(error);                                  // PID control을 이용하여 에러를 해결
       
    leftSpeed = headingLoop.m_command;                          // left speed 변화
    rightSpeed = -headingLoop.m_command;                        // right speed 변화

    leftSpeed += motorSpeed;                                    // total left speed 계산
    rightSpeed += (motorSpeed-motorOffset);                     // total right speed 계산
  }
  Serial.println(String()+leftSpeed+","+rightSpeed);            // 시리얼 모니터에 left, right speed 나타내기
  LeftFront.setSpeed(leftSpeed);                                
  LeftBack.setSpeed(leftSpeed); 
  RightBack.setSpeed(rightSpeed);
  RightFront.setSpeed(rightSpeed);                              // 새로운 모터 스피드 설정
}

void trackingStop_ID1()                                             // ID1 tracking function
{
  int32_t error;
  if (!huskylens.request(ID1))                                  // 연결이 안됐을 때
  {
    Serial.println(F("Check connection to Huskeylens"));
    stop();
  }
  else if(!huskylens.isLearned())                               // 학습이 안됐을 때
  {
    Serial.println(F("No object has been learned"));
    stop();

  }
  else if(!huskylens.available())                               // 스크린에 화살표가 표시되지 않은 경우
  {  Serial.println(F("No arrow on the screen yet"));
    stop();

  }	
  else                                                          // 선이 감지되고 화면에 표시 될때
  {
    stop();

  }
                               
}

void tracking_ID2()
{
  int32_t error;
  if (!huskylens.request(ID2))                                  // 연결이 안됐을 때
  {
    Serial.println(F("Check connection to Huskeylens"));
    leftSpeed = 0; 
    rightSpeed = 0;
  }
  else if(!huskylens.isLearned())                               // 학습이 안됐을 때
  {
    Serial.println(F("No object has been learned"));
    leftSpeed = 0; 
    rightSpeed = 0;
  }
  else if(!huskylens.available())                               // 스크린에 화살표가 표시되지 않은 경우
  {  Serial.println(F("No arrow on the screen yet"));
    leftSpeed = 0; 
    rightSpeed = 0;
  }	
  else                                                          // 선이 감지되고 화면에 표시 될때
  {
    HUSKYLENSResult result = huskylens.read();                  // 읽고 결과를 표시한다
    printResult(result);
    
    error = (int32_t)result.xTarget - (int32_t)160;             // 트래킹 에러 계산
    headingLoop.update(error);                                  // PID control을 이용하여 에러를 해결
       
    leftSpeed = headingLoop.m_command;                          // left speed 변화
    rightSpeed = -headingLoop.m_command;                        // right speed 변화

    leftSpeed += motorSpeed;                                    // total left speed 계산
    rightSpeed += (motorSpeed-motorOffset);                     // total right speed 계산
  }
  Serial.println(String()+leftSpeed+","+rightSpeed);            // 시리얼 모니터에 left, right speed 나타내기
  LeftFront.setSpeed(leftSpeed);                                
  LeftBack.setSpeed(leftSpeed); 
  RightBack.setSpeed(rightSpeed);
  RightFront.setSpeed(rightSpeed);                              // 새로운 모터 스피드 설정
}

void printResult(HUSKYLENSResult result)                    // 시리얼 모니터에 결과 출력
{
    if (result.command == COMMAND_RETURN_BLOCK)
    {
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW)
    {
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else
    {
        Serial.println("Object unknown!");
    }
}
