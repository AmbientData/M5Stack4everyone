#include <M5Stack.h>
#include "utility/MPU9250.h"

MPU9250 IMU;  // MPU9250のオブジェクトを定義

void drawGrid() {  // 座標を描く
    M5.Lcd.drawLine(41, 120, 279, 120, CYAN);
    M5.Lcd.drawLine(160, 1, 160, 239, CYAN);
    M5.Lcd.drawCircle(160, 120, 119, CYAN);
    M5.Lcd.drawCircle(160, 120, 60, CYAN);
}

// 泡に相当する点を描く. x, yは加速度（ミリG）で約-1000〜約1000
void drawSpot(int ax, int ay) {
    int x, y;
    x = map(constrain(ax, -300, 300), -300, 300, 40, 280);  // -300〜300までを40〜280にマッピング
    y = map(constrain(ay, -300, 300), -300, 300, 240, 0);   // -300〜300までを240〜0にマッピング
    M5.Lcd.fillScreen(BLACK);
    drawGrid();                              // 座標を描く
    M5.Lcd.fillCircle(x, y, 7, WHITE);       // 新しい点を描く
}

void setup() {
    M5.begin();  // M5Stackを初期化する
    Wire.begin();  // I2C通信を初期化
    IMU.initMPU9250();  // MPU9250を初期化
    IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias);  // MPU9250をキャリブレート
}

void loop() {
    float ax, ay;

    while (! (IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)) ;  // 10.4m秒ほどかかる
    IMU.readAccelData(IMU.accelCount);  // 加速度データを取得する
    IMU.getAres();                      // スケールを取得する

    ax = (float)IMU.accelCount[0] * IMU.aRes; // 加速度データを計算する
    ay = (float)IMU.accelCount[1] * IMU.aRes;

    drawSpot((int)(ax * 1000), (int)(ay * 1000));  // 泡に相当する点を描く
    delay(100);
}
