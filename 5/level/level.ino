#include <M5Stack.h>
#include "utility/MPU9250.h"

#define MULTISAMPLE 20  // 複数回測定する回数

MPU9250 IMU;  // MPU9250のオブジェクトを定義

void readAccelMulti(float * accel, int multi) {  // 加速度を複数(multi)回測定して、平均する  ---課題2の対策
    float ax, ay, az;

    ax = ay = az = 0.0;
    for (int i = 0; i < multi; i++) {
        while (! (IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)) ;  // 10.4m秒ほどかかる
        IMU.readAccelData(IMU.accelCount);  // 加速度データを取得する
        IMU.getAres();                      // スケールを取得する
        ax += (float)IMU.accelCount[0] * IMU.aRes;  // データを複数回足し込む
        ay += (float)IMU.accelCount[1] * IMU.aRes;
        az += (float)IMU.accelCount[2] * IMU.aRes;
    }
    accel[0] = ax / multi;  // 平均値を計算する
    accel[1] = ay / multi;
    accel[2] = az / multi;
}

void drawGrid() {  // 座標を描く
    M5.Lcd.drawLine(41, 120, 279, 120, CYAN);
    M5.Lcd.drawLine(160, 1, 160, 239, CYAN);
    M5.Lcd.drawCircle(160, 120, 119, CYAN);
    M5.Lcd.drawCircle(160, 120, 60, CYAN);
}

int oldx = 0;  // 古い点の座標  ---課題4の対策
int oldy = 0;

// アナログの水準器における「泡」に相当する点を描く。x, yは加速度（ミリg）で約-1000〜約1000
void drawSpot(int x, int y) {
    x = map(constrain(x, -300, 300), -300, 300, 40, 280);  // -300〜300までを40〜280にマッピング
    y = map(constrain(y, -300, 300), -300, 300, 240, 0);   // -300〜300までを240〜0にマッピング
    M5.Lcd.fillCircle(oldx, oldy, 7,BLACK);  // 古い点を消す  ---課題4の対策
    drawGrid();                              // 座標を描く
    M5.Lcd.fillCircle(x, y, 7, WHITE);       // 新しい点を描く
    oldx = x;  // 今描いた点を記録
    oldy = y;
}

float offset[3];  // オフセット  ---課題1の対策
#define MOVINGAVG 10  // 移動平均の長さ  ---課題3の対策
float movingavgx[MOVINGAVG], movingavgy[MOVINGAVG];  // 移動平均バッファ
int _indx = 0;  // 移動平均のインデックス

void setup() {
    M5.begin();  // M5Stackを初期化する
    Wire.begin();  // I2C通信を初期化
    IMU.initMPU9250();  // MPU9250を初期化
    IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias);  // MPU9250をキャリブレート

    readAccelMulti(offset, MULTISAMPLE);  // 加速度データを取得し、オフセット値にする  ---課題1の対策
    for (int i = 0; i < MOVINGAVG; i++) {  // 移動平均バッファの初期値をセット  ---課題3の対策
        movingavgx[i] = offset[0];
        movingavgy[i] = offset[1];
    }
}

void loop() {
    float ax, ay;
    float accel[3];

    M5.update();
    
    readAccelMulti(accel, MULTISAMPLE);  // 加速度データを取得  ---課題2の対策

    // 移動平均を計算  ---課題3の対策
    movingavgx[_indx] = accel[0];
    movingavgy[_indx] = accel[1];
    _indx = (_indx + 1) % MOVINGAVG;
    ax = ay = 0;
    for (int i = 0; i < MOVINGAVG; i++) {
        ax += movingavgx[i];
        ay += movingavgy[i];
    }
    ax /= MOVINGAVG;
    ay /= MOVINGAVG;

    if (M5.BtnA.wasPressed()) {  // ボタンAが押されていたら  ---課題1の対策
        offset[0] = ax;  // 現在の加速度データをオフセット値にセット
        offset[1] = ay;
    }
    drawSpot((int)((ax - offset[0]) * 1000), (int)((ay - offset[1]) * 1000));  // ---課題1の対策
    delay(100);
}
