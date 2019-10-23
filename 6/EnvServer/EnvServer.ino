#include <M5Stack.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "Adafruit_Si7021.h"

const char* ssid = "myssid";
const char* password = "mypassword";

WebServer server(80);  // WebServerオブジェクトを作る

Adafruit_Si7021 sensor = Adafruit_Si7021();  // Adafruit_Si7021オブジェクトを初期化する

void handleRoot() {  // "/"をアクセスされたときの処理関数
    server.send(200, "text/plain", "hello from M5Stack!");
    M5.Lcd.println("accessed on \"/\"");
}

void handleEnv() { // "/env"をアクセスされたときの処理関数
    char buf[400];  // HTMLを編集する文字配列
    float temp = sensor.readTemperature();   // Si7021から温度を読む
    float humid = sensor.readHumidity();     // Si7021から湿度を読む

    M5.Lcd.printf("Temp: %.1f, Humid: %.1f\r\n", temp, humid);
    sprintf(buf,  // HTMLに温度と湿度を埋め込む
        "<html>\
         <head>\
            <title>M5Stack EvnServer</title>\
         <head>\
         <body>\
            <h1>M5Stack EnvServer</h1>\
            <p>Temp: %.1f 'C</p>\
            <p>Humid: %.1f %%</p>\
         </body>\
         </html>",
    temp, humid);
    server.send(200, "text/html", buf);
}

void handleNotFound() {  // 存在しないファイルにアクセスされたときの処理関数
    server.send(404, "text/plain", "File Not Found\n\n");
    M5.Lcd.println("File Not Found");
}

void setup(void) {
    M5.begin();

    WiFi.begin(ssid, password);  // Wi-Fi APに接続する
    while (WiFi.status() != WL_CONNECTED) {  //  Wi-Fi AP接続待ち
        delay(500);
        M5.Lcd.print(".");
    }
    M5.Lcd.print("\r\nWiFi connected\r\nIP address: ");
    M5.Lcd.println(WiFi.localIP());

  if (MDNS.begin("m5stack")) {
    Serial.println("MDNS responder started");
  }

    server.on("/", handleRoot);
    server.on("/env", handleEnv);
    server.onNotFound(handleNotFound);

    server.begin();
    M5.Lcd.println("HTTP server started");

    if (!sensor.begin()) {  // Si7021を初期化する
        Serial.println("Did not find Si7021 sensor!");
        while (true) {
            delay(0);
        }
    }
}

void loop(void) {
  server.handleClient();
}
