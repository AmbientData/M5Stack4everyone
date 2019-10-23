/*
 * 磁気センサーの値をシリアルに出力する
 */
#include <M5Stack.h>
#include "utility/MPU9250.h"

#define MULTISAMPLE 10  // 複数回測定する回数

MPU9250 IMU;  // MPU9250のオブジェクトを定義

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

void setup() {
    M5.begin();  // M5Stackを初期化する
    Wire.begin();  // I2C通信を初期化
    IMU.initMPU9250();  // MPU9250を初期化
    IMU.initAK8963(IMU.magCalibration);  // AK8963をキャリブレート

    Serial.begin(115200);  // シリアル回線を初期化
    while (!Serial) ;  // シリアル回線が準備できるまで待つ
}

void loop() {
    float mag[3];

    readMagMulti(mag, MULTISAMPLE);

    Serial.printf("%.0f, %.0f, %.0f\r\n", mag[0], mag[1], mag[2]);
}
