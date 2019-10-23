#include <M5Stack.h>
#include "SG90.h"
#include <Wire.h>

float ncirtemperature();
uint32_t heat(float);           // heat関数の宣言

#define CX 16    // x方向のセルの分割数
#define CY 16    // y方向のセルの分割数

SG90 pan;               // 水平方向を制御するSG90のインスタンス
SG90 tilt;              // 上下方向を制御するSG90のインスタンス

#define WIDTH (320 / CX)      // LCDに表示するセルの横幅
#define HEIGHT (240 / CY)     // LCDに表示するセルの縦幅

void drawTemp(int cx, int cy, float t) {  // セル (cx, cy) に温度に対応した色を塗る
    uint16_t color = heat(map(constrain((int)t, 20, 60), 20, 60, 0, 100) / 100.0);
    M5.Lcd.fillRect(cx * WIDTH, cy * HEIGHT, WIDTH, HEIGHT, color);
    M5.Lcd.setCursor(cx * WIDTH + 5, cy * HEIGHT + HEIGHT / 2);  // セル中央にカーソルを設定
    M5.Lcd.setTextColor(BLACK, color);
    M5.Lcd.printf("%d", (int)t);  // 温度を数値で表示
}

void setup() {
    M5.begin();
    Wire.begin();

    pan.begin(2, 15);   // GPIO2、チャネル15で初期化
    tilt.begin(5, 14);  // GPIO5、チャネル14で初期化

    for (int cy = 0; cy < CY; cy++) {
        float ly = (float)map(cy, 0, CY, 100, -100) / 100.0 - 1.0 / (float)CY;
        tilt.write(int(degrees(atan2(ly, 1))));
        for (int cx = 0; cx < CX; cx++) {
            float lx = (float)map(cx, 0, CX, -100, 100) / 100.0 + 1.0 / (float)CX;
            pan.write(int(degrees(atan2(lx, 1))));

            delay(300);    // MLX90614のデータが安定するまでの時間
            drawTemp(cx, cy, ncirtemperature());
        }
    }
    pan.write(0);
    tilt.write(0);
}

void loop() {
}
