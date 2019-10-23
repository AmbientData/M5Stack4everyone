#include <M5Stack.h>
#include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();  // Adafruit_Si7021オブジェクトを初期化する

void setup() {
    M5.begin();  // M5Stackを初期化する

    if (!sensor.begin()) {  // Si7021を初期化する
        Serial.println("Did not find Si7021 sensor!");
        while (true) {
            delay(0);
        }
    }

    M5.Lcd.setTextSize(3);
}

void loop() {
    float temp = sensor.readTemperature();   // Si7021から温度を読む
    float humid = sensor.readHumidity();     // Si7021から湿度を読む

    M5.Lcd.setCursor(40, 80);
    M5.Lcd.print("Temp: ");
    M5.Lcd.print(temp, 1);                   // 温度をLCDに表示
    M5.Lcd.print("'C");
    M5.Lcd.setCursor(40, 140);
    M5.Lcd.print("Humid: ");
    M5.Lcd.print(humid, 1);                  // 湿度をLCDに表示
    M5.Lcd.print("%");
    delay(1000);
}
