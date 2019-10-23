#include <M5Stack.h>
#include "Adafruit_Si7021.h"
#include "SG90.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();  // Adafruit_Si7021オブジェクトを初期化する
SG90 sg90;              // SG90のオブジェクトを作る

void setup() {
    M5.begin();  // M5Stackを初期化する

    sensor.begin();  // Si7021を初期化する
    sg90.begin(2, 15);  // SG90を初期化する
}

void loop() {
    float temp = sensor.readTemperature();   // Si7021から温度を読む

    // 温度に応じてモーターの角度を変える
    sg90.write(map(constrain((int)temp, -10, 40), -10, 40, -90, -40));

    delay(1000);
}
