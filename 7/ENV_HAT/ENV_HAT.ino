#include <M5StickC.h>
#include "DHT12.h"
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>

DHT12 dht12; 
Adafruit_BMP280 bme;

void setup() {
    M5.begin();
    M5.Lcd.setRotation(3);      // 左を上にする
    M5.Lcd.fillScreen(BLACK);   // 背景を黒にする
    M5.Lcd.setCursor(0, 0, 2);
    M5.Lcd.println("ENV TEST");

    Wire.begin(0, 26);          // I2Cを初期化する
    if (!bme.begin(0x76)){      // BMP280を初期化する
        M5.Lcd.println("Could not find a valid BMP280 sensor, check wiring!");
        while (1);
    }
}

void loop() {
    float tmp = dht12.readTemperature();              // DHT12から温度を取得
    float hum = dht12.readHumidity();                 // DHT12から湿度を取得
    float pressure = bme.readPressure() / 100;        // BMP280から気圧を取得
    double vbat = M5.Axp.GetVbatData() * 1.1 / 1000;  // バッテリー電圧を取得

    M5.Lcd.setCursor(0, 20);
    M5.Lcd.printf("Temp: %4.1f Humi: %4.1f", tmp, hum);
    M5.Lcd.setCursor(0, 40);
    M5.Lcd.printf("pressure: %4.0f", pressure);
    M5.Lcd.setCursor(0, 60);
    M5.Lcd.printf("vbat: %4.2f", vbat);
    delay(100);
}
