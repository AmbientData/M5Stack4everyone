// #include <M5Stack.h> より前に #define する
#define M5STACK_MPU6886 
// #define M5STACK_MPU9250 

#include <M5Stack.h>

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

void setup() {
    M5.begin();
    M5.Power.begin();
    
    M5.IMU.Init();  // IMUチップを初期化する

    M5.Lcd.setTextSize(2);
}

void loop() {
    M5.IMU.getAccelData(&accX,&accY,&accZ);  // IMUから加速度データを取得する
  
    M5.Lcd.setCursor(0, 65);
    M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);
    M5.Lcd.setCursor(220, 87);
    M5.Lcd.print(" G");

    delay(1);
}
