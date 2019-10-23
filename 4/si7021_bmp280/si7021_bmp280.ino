#include <M5Stack.h>
#include "Adafruit_Si7021.h"
#include "Seeed_BMP280.h"
#include <Wire.h>

Adafruit_Si7021 sensor = Adafruit_Si7021();  // Adafruit_Si7021オブジェクトを初期化する
BMP280 bmp280;  // BMP280オブジェクトを定義する

void setup() {
    M5.begin();  // M5Stackを初期化する

    if (!sensor.begin()) {  // Si7021を初期化する
        Serial.println("Did not find Si7021 sensor!");
        while (true) ;
    }
    if(!bmp280.init()) { // BMP280を初期化する
        Serial.println("Device not connected or broken!");
        while (true) ;
    }
    M5.Lcd.setTextSize(3);
}

void loop() {
    float temp = sensor.readTemperature();           // Si7021から温度を読む
    float humid = sensor.readHumidity();             // Si7021から湿度を読む
    float bmp280temp = bmp280.getTemperature();      // BMP280から温度を読む
    uint32_t pressure = bmp280.getPressure();        // BMP280から気圧を読む
    float altitude = bmp280.calcAltitude(pressure);  // 高度を計算する

    M5.Lcd.setCursor(40, 30);
    M5.Lcd.printf("Temp: %5.1f'C", temp);            // 温度をLCDに表示
    M5.Lcd.setCursor(40, 70);
    M5.Lcd.printf("Humid: %5.1f%%", humid);          // 湿度をLCDに表示

    M5.Lcd.setCursor(40, 110);
    M5.Lcd.printf("Temp: %5.1f'C", bmp280temp);      // BMP280の温度を表示  ----④
    M5.Lcd.setCursor(40, 150);
    M5.Lcd.printf("Press: %dhPa", pressure / 100);   // 気圧を表示
    M5.Lcd.setCursor(40, 190);
    M5.Lcd.printf("Alti: %5.2fm", altitude);         // 高度を表示

    delay(1000);
}
