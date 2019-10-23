#include "SG90.h"
#include <M5Stack.h>

void SG90::begin(int pin, int ch) {
    _ch = ch;
    ledcSetup(_ch, 50, 10);
    ledcAttachPin(pin, _ch);
    SG90::write(0);
}

void SG90::write(int angle) {
    ledcWrite(_ch, map(constrain(angle, -90, 90), -90, 90, _max, _min));
}
