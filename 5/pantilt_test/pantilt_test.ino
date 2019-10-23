#include <M5Stack.h>
#include "SG90.h"

SG90 pan;               // 水平方向を制御するSG90のオブジェクト
SG90 tilt;              // 上下方向を制御するSG90のオブジェクト

void setup() {
    pan.begin(2, 15);   // GPIO2、チャネル15で初期化
    delay(500);
    tilt.begin(5, 14);  // GPIO5、チャネル14で初期化
    delay(500);

    for (int a = -90; a <= 90; a += 10) {
        pan.write(a);   // 10°ずつ右を向く
        delay(50);
    }
    pan.write(0);       // 水平方向、正面を向く
    delay(500);

    for (int a = -90; a <= 90; a += 10) {
        tilt.write(a);  // 10°ずつ上を向く
        delay(50);
    }
    tilt.write(0);      // 上下方向、正面を向く
}

void loop() {
}
