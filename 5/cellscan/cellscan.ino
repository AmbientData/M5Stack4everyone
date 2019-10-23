#include <M5Stack.h>
#include "SG90.h"

#define CX 16           // x方向のセルの分割数
#define CY 16           // y方向のセルの分割数

SG90 pan;               // 水平方向を制御するSG90のオブジェクト
SG90 tilt;              // 上下方向を制御するSG90のオブジェクト

void setup() {
    M5.begin();

    pan.begin(2, 15);   // GPIO2、チャネル15で初期化
    delay(500);
    tilt.begin(5, 14);  // GPIO5、チャネル14で初期化
    delay(500);

    for (int cy = 0; cy < CY; cy++) {
        float ly = (float)map(cy, 0, CY, 100, -100) / 100.0 - 1.0 / (float)CY;
        tilt.write(int(degrees(atan2(ly, 1))));
        for (int cx = 0; cx < CX; cx++) {
//            int xx = (cy % 2 == 0) ? cx : CX - 1 - cx;
//            float lx = (float)map(xx, 0, CX, -100, 100) / 100.0 + 1.0 / (float)CX;
            float lx = (float)map(cx, 0, CX, -100, 100) / 100.0 + 1.0 / (float)CX;
            pan.write(int(degrees(atan2(lx, 1))));
            delay(300);
        }
    }
    pan.write(0);
    tilt.write(0);
}

void loop() {
}
