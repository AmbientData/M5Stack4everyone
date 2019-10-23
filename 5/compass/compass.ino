#include <M5Stack.h>
#include "utility/MPU9250.h"

#define MULTISAMPLE 10  // 複数回測定する回数

MPU9250 IMU;  // MPU9250のオブジェクトを定義

void beep(int freq, int duration, uint8_t volume);
void drawLineByAngle(int16_t x, int16_t y, int16_t start, int16_t length, int16_t angle, int thick, uint16_t color);

void readMagMulti(float * mag, int multi) {  // 磁気を複数(multi)回測定して、平均する
    float mx, my, mz;

    mx = my = mz = 0.0;
    for (int i = 0; i < multi; i++) {
        while (! (IMU.readByte(AK8963_ADDRESS, AK8963_ST1) & 0x01)) ;
        IMU.readMagData(IMU.magCount);  // MPU9250の磁気データを取得
        IMU.getMres(); // get accelerometer scales saved to "aRes"
        mx += (float)IMU.magCount[0] * IMU.mRes * IMU.magCalibration[0] - IMU.magbias[0];  // データを複数回足し込む
        my += (float)IMU.magCount[1] * IMU.mRes * IMU.magCalibration[1] - IMU.magbias[1];
        mz += (float)IMU.magCount[2] * IMU.mRes * IMU.magCalibration[2] - IMU.magbias[2];
    }
    mag[0] = mx / multi;  // 平均値を計算する
    mag[1] = my / multi;
    mag[2] = mz / multi;
}

void drawGrid() {
    for (int i = 0; i < 360; i += 5) {  // 5°ごとの目盛りを描く
        drawLineByAngle(160, 120, 100 - 10, 10, i, 1, WHITE);
    }
    for (int i = 0; i < 360; i += 30) {  // 30°ごとの目盛りを描く
        drawLineByAngle(160, 120, 100 - 15, 15, i, 1, WHITE);
        int y = 120 - 115 * cos(radians(i));
        if (i == 180) y -= 7;
        M5.Lcd.setCursor(160 + 115 * sin(radians(i)) - 5, y);
        if (i % 90 == 0) {  // 90°ごとにN、E、S、Wを書く
            M5.Lcd.print("NESW"[i / 90]);
        } else {
            M5.Lcd.print(i);
        }
    }
}

float offset[2];  // オフセット

void setup() {
    M5.begin();  // M5Stackを初期化する
    Wire.begin();  // I2C通信を初期化
    IMU.initMPU9250();
    IMU.initAK8963(IMU.magCalibration);

    float mag[3];
    float minX, maxX, minY, maxY;
    minX = minY = 10000.0;
    maxX = maxY = -10000.0;

    for (int i = 0; i < 16; i++) {
        readMagMulti(mag, MULTISAMPLE);  // 磁力を測る
        minX = min(minX, mag[0]);  // 最小値を見つける
        minY = min(minY, mag[1]);
        maxX = max(maxX, mag[0]);  // 最大値を見つける
        maxY = max(maxY, mag[1]);
        beep(1000, 100, 2);        // ピッと鳴らす
    }
    beep(1000, 500, 2);
    offset[0] = (minX + maxX) / 2;  // 最小値と最大値の真ん中をオフセット値にする
    offset[1] = (minY + maxY) / 2;

    drawGrid();
}

int oldangle = 0;

void loop() {
    float mx, my;
    float mag[3];

    readMagMulti(mag, MULTISAMPLE);  // 磁力を測る

    mx = mag[0] - offset[0];
    my = mag[1] - offset[1];
    int angle = (int)degrees(atan2(my, mx));

    drawLineByAngle(160, 120, 0, 85, oldangle, 1, BLACK);  // 古い線を消す
    drawLineByAngle(160, 120, 0, 85, oldangle - 180, 1, BLACK);
    drawLineByAngle(160, 120, 0, 85, angle, 1, RED);  // 新しい線の北側を描く
    drawLineByAngle(160, 120, 0, 85, angle - 180, 1, WHITE);  // 南側を描く

    oldangle = angle;
}
