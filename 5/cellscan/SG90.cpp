#include "SG90.h"
#include <M5Stack.h>

#define DELAYPERDEG 2.0

void SG90::begin(int pin, int ch) {
    _ch = ch;
    _angle = 0;
    ledcSetup(_ch, 50, 10);
    ledcAttachPin(pin, _ch);
    SG90::write(0);
}

void SG90::write(int angle) {
    ledcWrite(_ch, map(constrain(angle, -90, 90), -90, 90, _max, _min));
    delay((int)(DELAYPERDEG * abs(_angle - angle)));  // 前の角度から今の角度に動き終わるまで待つ
    _angle = constrain(angle, -90, 90);
}
