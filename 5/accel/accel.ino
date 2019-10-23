#include <M5Stack.h>
#include "utility/MPU9250.h"

MPU9250 IMU;  // MPU9250のオブジェクトを定義

void setup() {
    M5.begin();  // M5Stackを初期化する
    Wire.begin();  // I2C通信を初期化
    IMU.initMPU9250();  // MPU9250を初期化
    IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias);  // MPU9250をキャリブレート

    M5.Lcd.setTextSize(2);
}

void loop() {
    if (IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01) {  // データが取得可能か調べる
        IMU.readAccelData(IMU.accelCount);                   // 加速度データを取得する
        IMU.getAres();                                       // スケールを取得する
        IMU.ax = (float)IMU.accelCount[0] * IMU.aRes;        // 加速度データを計算する
        IMU.ay = (float)IMU.accelCount[1] * IMU.aRes;
        IMU.az = (float)IMU.accelCount[2] * IMU.aRes;
        M5.Lcd.clear();
        M5.Lcd.setCursor(0, 0);  M5.Lcd.print("MPU9250 acceleration");
        M5.Lcd.setCursor(0, 32); M5.Lcd.printf("X: %7.2f mG", 1000 * IMU.ax);
        M5.Lcd.setCursor(0, 64); M5.Lcd.printf("Y: %7.2f mG", 1000 * IMU.ay);
        M5.Lcd.setCursor(0, 96); M5.Lcd.printf("Z: %7.2f mG", 1000 * IMU.az);
    }
    delay(200);
}
