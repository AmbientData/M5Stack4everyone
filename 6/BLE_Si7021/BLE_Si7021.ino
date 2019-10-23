#include <M5Stack.h>
#include "BLEDevice.h"
#include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();  // Adafruit_Si7021オブジェクトを初期化する

#define T_PERIOD     10  // Transmission period
#define S_PERIOD     10  // Silent period

BLEAdvertising *pAdvertising;
uint8_t seq = 0;  // シーケンス番号

void setAdvData(BLEAdvertising *pAdvertising) {
    uint16_t temp = (uint16_t)(sensor.readTemperature() * 100);  // Si7021から温度を読む
    uint16_t humid = (uint16_t)(sensor.readHumidity() * 100);  // Si7021から湿度を読む
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

void setup(void) {
    M5.begin();
    M5.Lcd.setTextSize(2);

    if (!sensor.begin()) {  // Si7021を初期化する
        M5.Lcd.println("Did not find Si7021 sensor!");
        while (true) {
            delay(0);
        }
    }
    BLEDevice::init("M5Stack Env");      // デバイスを初期設定
    BLEServer *pServer = BLEDevice::createServer();    // サーバーを生成
    pAdvertising = pServer->getAdvertising(); // アドバタイズオブジェクトを取得
}

void loop(void) {
    setAdvData(pAdvertising);                          // アドバタイジングデーターをセット

    pAdvertising->start();                             // アドバタイズ開始
    M5.Lcd.print("Advertize start...");
    delay(T_PERIOD * 1000);                            // T_PERIOD秒アドバタイズする
    pAdvertising->stop();                              // アドバタイズ停止
    M5.Lcd.println("stop");
    delay(S_PERIOD * 1000);                            // S_PERIOD秒休む

    seq++;                                             // シーケンス番号を更新
}
