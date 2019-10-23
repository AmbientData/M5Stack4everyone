#include <M5Stack.h>
#include <WiFi.h>

const char* ssid = "myssid";
const char* password = "mypassword";

void setup() {
    M5.begin();
    M5.Lcd.setTextSize(2);

    WiFi.begin(ssid, password);  // Wi-Fi APに接続する
    while (WiFi.status() != WL_CONNECTED) {  //  Wi-Fi AP接続待ち
        delay(500);
        M5.Lcd.print('.');
    }

    M5.Lcd.print("\r\nWiFi connected\r\nIP address: ");
    M5.Lcd.println(WiFi.localIP());
}

void loop() {
}
