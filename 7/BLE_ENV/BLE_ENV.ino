#include <M5StickC.h>
#include "BLEDevice.h"
#include "DHT12.h"
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>

DHT12 dht12; 
Adafruit_BMP280 bme;

#define T_PERIOD     10  // Transmission period
#define S_PERIOD     10  // Silent period

BLEAdvertising *pAdvertising;
uint8_t seq = 0;  // シーケンス番号

void setAdvData(BLEAdvertising *pAdvertising) {
    uint16_t temp = (uint16_t)(dht12.readTemperature() * 100);  // DHT12から温度を読む
    uint16_t humid = (uint16_t)(dht12.readHumidity() * 100);  // DHT12から湿度を読む
    M5.Lcd.printf("temp: %d, humid: %d\r\n", temp, humid);

    BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
    oAdvertisementData.setFlags(0x06); // BR_EDR_NOT_SUPPORTED | LE General Discoverable Mode

    std::string strServiceData = "";
    strServiceData += (char)0x08;   // 長さ
    strServiceData += (char)0xff;   // AD Type 0xFF: Manufacturer specific data
    strServiceData += (char)0xff;   // Test manufacture ID low byte
    strServiceData += (char)0xff;   // Test manufacture ID high byte
    strServiceData += (char)seq;                   // シーケンス番号
    strServiceData += (char)(temp & 0xff);         // 温度の下位バイト
    strServiceData += (char)((temp >> 8) & 0xff);  // 温度の上位バイト
    strServiceData += (char)(humid & 0xff);        // 湿度の下位バイト
    strServiceData += (char)((humid >> 8) & 0xff); // 湿度の上位バイト

    oAdvertisementData.addData(strServiceData);
    pAdvertising->setAdvertisementData(oAdvertisementData);
}

void setup() {
    M5.begin();
    M5.Lcd.setRotation(3);      // 左を上にする

    Wire.begin(0,26);           // I2Cを初期化する
    if (!bme.begin(0x76)){      // BMP280を初期化する
        M5.Lcd.println("Could not find a valid BMP280 sensor, check wiring!");
        while (1);
    }
    BLEDevice::init("M5StickC Env");      // デバイスを初期設定
    BLEServer *pServer = BLEDevice::createServer();    // サーバーを生成
    pAdvertising = pServer->getAdvertising(); // アドバタイズオブジェクトを取得
}

void loop() {
    M5.Lcd.fillScreen(BLACK);   // 背景を黒にする
    M5.Lcd.setCursor(0, 0, 2);
    setAdvData(pAdvertising);                          // アドバタイジングデーターをセット

    pAdvertising->start();                             // アドバタイズ開始
    M5.Lcd.print("Advertizing started...");
    delay(T_PERIOD * 1000);                            // T_PERIOD秒アドバタイズする
    pAdvertising->stop();                              // アドバタイズ停止
    M5.Lcd.println("stopped.");
    delay(S_PERIOD * 1000);                            // S_PERIOD秒休む

    seq++;                                             // シーケンス番号を更新
}
