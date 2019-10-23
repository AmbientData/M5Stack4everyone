#include <M5Stack.h>
#include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();  // Adafruit_Si7021オブジェクトを初期化する

#define LED_PIN 2

int WBGTlevel(float humid, float temp) {  // 熱中症の危険度を計算する
    if (temp > (humid * (-12.0 / 70.0) + 40.0 + 36.0 / 7.0))
        return 3;  // 危険
    if (temp > humid * (-13.0 / 80.0) + 25.0 + 130.0 / 8.0)
        return 2;  // 厳重警戒
    if (temp > humid * (-3.0 / 20.0) + 37.0)
        return 1;  // 警戒
    else
        return 0;  // 注意
}

void setup() {
    M5.begin();  // M5Stackを初期化する
    pinMode(LED_PIN, OUTPUT);  // GPIO2を出力モードに設定する

    if (!sensor.begin()) {  // Si7021を初期化する
        Serial.println("Did not find Si7021 sensor!");
        while (true) ;
    }

    M5.Lcd.setTextSize(3);
}

void loop() {
    float temp = sensor.readTemperature();   // Si7021から温度を読む
    float humid = sensor.readHumidity();     // Si7021から湿度を読む

    M5.Lcd.setCursor(40, 80);
    M5.Lcd.printf("Temp: %5.1f'C", temp);    // 温度をLCDに表示
    M5.Lcd.setCursor(40, 140);
    M5.Lcd.printf("Humid: %5.1f%%", humid);  // 湿度をLCDに表示

    if (WBGTlevel(humid, temp) > 1) {  // 熱中症の危険度を計算し、危険か厳重警戒なら
        digitalWrite(LED_PIN, HIGH);   // LEDを点ける
    } else {                           // そうでないなら
        digitalWrite(LED_PIN, LOW);    // LEDを消す
    }
    delay(1000);
}
