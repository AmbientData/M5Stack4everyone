/*
 * SG90をPWMで制御するテストプログラム
 */
#include <M5Stack.h>
#include "SG90.h"       // クラスライブラリのヘッダファイルをインクルードする

SG90 sg90;              // SG90のオブジェクトを作る

void setup() {
    M5.begin();

    sg90.begin(2, 15);  // SG90を初期化する

    for (int angle = -90; angle <= 90; angle += 5) {  // 角度を-90°から90°まで5°ずつ増やす
        sg90.write(angle);  // SG90のモーターを指定した角度に回す
        delay(100);
    }
}

void loop() {
}
