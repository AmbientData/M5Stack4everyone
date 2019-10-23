/*
 * SG90をPWMで制御するテストプログラム
 */
#include <M5Stack.h>

void SG90write(int angle) {
    ledcWrite(15, map(constrain(angle, -90, 90), -90, 90, 123, 26));  // -90°〜90°を26〜123に比例計算
}

void setup() {
    M5.begin();

    ledcSetup(15, 50, 10);  // (チャネル, 周波数, 分解能)
    ledcAttachPin(2, 15);   // (ピン番号, チャネル)

    for (int angle = -90; angle <= 90; angle += 5) {  // 角度を-90°から90°まで5°ずつ増やす
        SG90write(angle);
        delay(100);
    }
}

void loop() {
}
