#include <M5Stack.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "myssid";
const char* password = "mypassword";

WebServer server(80);  // WebServerオブジェクトを作る

void handleRoot() {  // "/"をアクセスされたときの処理関数
    server.send(200, "text/plain", "hello from M5Stack!");
    M5.Lcd.println("accessed on \"/\"");
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
        M5.Lcd.println("MDNS responder started");
    }

    server.on("/", handleRoot);
    server.onNotFound(handleNotFound);

    server.begin();
    M5.Lcd.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
