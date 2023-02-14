// C++ code
// to RGB on/off light
const int RED = 9; // 상수 선언과 동시에 초기화
const int GREEN = 10;
const int BLUE = 11;
void setup()
{
   pinMode(RED, OUTPUT); 
   pinMode(GREEN, OUTPUT);
   pinMode(BLUE, OUTPUT);

}

void loop()
{
  showSpectrum(); // 함수 원형 선언
}
void showSpectrum() // 함수 정의
{
  for (int x = 0; x < 768; x++)
  {
    showRGB(x); // 함수 선언
    delay(10);
  }
}

void showRGB(int color)
{
  int redIntensity;
  int greenIntensity;
  int blueIntensity;
  
  if (color <=255)
  {
    redIntensity = 255 - color;
    greenIntensity = color;
    blueIntensity = 0;
  }
  else if (color <= 511)
  {
    redIntensity = 0;
    greenIntensity = 255 - (color -256);
    blueIntensity = (color - 256);
  }
  else
  {
     redIntensity = (color - 512);
     greenIntensity = 0;
     blueIntensity = 255 -(color - 512);
  }
  
  analogWrite(RED,redIntensity);
  analogWrite(BLUE,blueIntensity);
  analogWrite(GREEN,greenIntensity);

}
// https://www.youtube.com/watch?v=1iBxocxqhD4


    
    
    
    
    
    
    
    
    
    
    
    
    