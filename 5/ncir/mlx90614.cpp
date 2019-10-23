#include <Wire.h>

#define NCIR_ADDR 0x5A

float ncirtemperature() {
    uint16_t result;

    Wire.beginTransmission(NCIR_ADDR);     // MLX90614のI2Cアドレスを送信
    Wire.write(0x07);                      // MLX90614内のアドレスを送信
    Wire.endTransmission(false);           // 通信を実行
    Wire.requestFrom(NCIR_ADDR, 2);        // MLX90614から2バイト送信要求
    result = Wire.read();                  // データの下位バイトを受信
    result |= Wire.read() << 8;            // データの上位バイトを受信

    return result * 0.02 - 273.15;         // 温度を計算
}
