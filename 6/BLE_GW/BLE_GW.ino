#include <M5Stack.h>
#include "BLEDevice.h"
#include "Ambient.h"

uint8_t seq;  // シーケンス番号
#define MyManufacturerId 0xffff  // test manufacturer ID

WiFiClient client;
const char* ssid = "myssid";
const char* password = "mypassword";

Ambient ambient;
unsigned int channelId = 100; // AmbientのチャネルID
const char* writeKey = "writeKey"; // ライトキー

BLEScan* pBLEScan;

void setup() {
    M5.begin();
    M5.Lcd.setTextSize(2);

    BLEDevice::init("");      // デバイスを初期設定
    pBLEScan = BLEDevice::getScan();  // スキャンオブジェクトを取得
    pBLEScan->setActiveScan(false);   // パッシブスキャンに設定

    WiFi.begin(ssid, password);  //  Wi-Fi APに接続
    while (WiFi.status() != WL_CONNECTED) {  //  Wi-Fi AP接続待ち
        M5.Lcd.print(".");
        delay(100);
    }
    M5.Lcd.print("\r\nWiFi connected\r\nIP address: ");
    M5.Lcd.println(WiFi.localIP());

    ambient.begin(channelId, writeKey, &client); // チャネルIDとライトキーを指定してAmbientの初期化
}

void loop() {
    bool found = false;
    float temp, humid;

    BLEScanResults foundDevices = pBLEScan->start(3);  // スキャンを開始
    int count = foundDevices.getCount();  // スキャンで見つけたデバイス数を取得
//    M5.Lcd.printf("BLE devs = %d\r\n", count);
    for (int i = 0; i < count; i++) {
        BLEAdvertisedDevice d = foundDevices.getDevice(i);  // 見つけたデバイスの情報を取得
        if (d.haveManufacturerData()) {  // マニュファクチャラデータを持っていたら
            std::string data = d.getManufacturerData();  // マニュファクチャラデータを取得
            int manu = data[1] << 8 | data[0];
            if (manu == MyManufacturerId && seq != data[2]) {
                found = true;
                seq = data[2];
                temp = (float)(data[4] << 8 | data[3]) / 100.0;
                humid = (float)(data[6] << 8 | data[5]) / 100.0;
                M5.Lcd.printf("> seq: %d, t: %.1f, h: %.1f\r\n", seq, temp, humid);
            }
        }
    }
    if (found) {
        ambient.set(1, temp);
        ambient.set(2, humid);
        ambient.send();        // 温度、湿度の値をAmbientに送信する
    }
}
