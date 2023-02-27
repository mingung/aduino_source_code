//조도센서를 이용하여 빛의 밝기를 lcd에 출력
#include <Wire.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C mylcd(34,16,2);


void setup(){
  mylcd.init();
  mylcd.backlight();
}

void loop(){
  int light = analogRead(A0);
  
  mylcd.clear(); // loop는 반복되기 때문에 새로 반복할때 지워주기 위함
  mylcd.setCursor(0,0);
  mylcd.print("Light: ");
  mylcd.setCursor(0,1);
  mylcd.print(light);
  delay(1000);
  
  
}
