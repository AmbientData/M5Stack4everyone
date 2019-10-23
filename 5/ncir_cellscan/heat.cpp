#include <Arduino.h>

float gain = 10.0;
float offset_x = 0.2;
float offset_green = 0.6;

float sigmoid(float x, float g, float o) {
    return (tanh((x + o) * g / 2) + 1) / 2;
}

uint32_t heat(float x) {  // 0.0〜1.0の値を青から赤の色に変換する
    x = x * 2 - 1;  // -1 <= x < 1 に変換

    float r = sigmoid(x, gain, -1 * offset_x);
    float b = 1.0 - sigmoid(x, gain, offset_x);
    float g = sigmoid(x, gain, offset_green) + (1.0 - sigmoid(x, gain, -1 * offset_green)) - 1;

    return (((int)(r * 255)>>3)<<11) | (((int)(g * 255)>>2)<<5) | ((int)(b * 255)>>3);
}
