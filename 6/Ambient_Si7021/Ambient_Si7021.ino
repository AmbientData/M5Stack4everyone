#include <M5Stack.h>
#include <WiFi.h>
#include "Adafruit_Si7021.h"
#include <Ambient.h>  // Ambientのヘッダファイルをインクルード

const char* ssid = "myssid";
const char* password = "mypassword";

WiFiClient client;
Ambient ambient;  // Ambientオブジェクトを作る

unsigned int channelId = 100; // AmbientのチャネルID
const char* writeKey = "writeKey"; // ライトキー

Adafruit_Si7021 sensor = Adafruit_Si7021();  // Adafruit_Si7021オブジェクトを初期化する

void setup(void) {
    M5.begin();

    WiFi.begin(ssid, password);  // Wi-Fi APに接続する
    while (WiFi.status() != WL_CONNECTED) {  //  Wi-Fi AP接続待ち
        delay(500);
        M5.Lcd.print(".");
    }
    M5.Lcd.print("\r\nWiFi connected\r\nIP address: ");
    M5.Lcd.println(WiFi.localIP());

    ambient.begin(channelId, writeKey, &client); // チャネルIDとライトキーを指定してAmbientを初期化

    if (!sensor.begin()) {  // Si7021を初期化する
        M5.Lcd.println("Did not find Si7021 sensor!");
        while (true) {
            delay(0);
        }
    }
}

void loop(void) {
    float temp = sensor.readTemperature();  // Si7021から温度を読む
    float humid = sensor.readHumidity();  // Si7021から湿度を読む
    M5.Lcd.printf("temp: %.2f, humid: %.2f\r\n", temp, humid);

    ambient.set(1, temp);  // Ambientのデータ1に温度をセットする
    ambient.set(2, humid);  // データ2に湿度をセットする
    ambient.send();  // Ambientに送信する

    delay(60 * 1000);
}
