#include <M5Stack.h>

#define LED_PIN 2

void setup() {
    M5.begin();  // M5Stackを初期化する
    pinMode(LED_PIN, OUTPUT);  // GPIO2を出力モードに設定する
}

void loop() {
    digitalWrite(LED_PIN, HIGH);  // GPIO2をHIGHにする
    delay(500);                   // 0.5秒待つ
    digitalWrite(LED_PIN, LOW);   // GPIO2をLOWにする
    delay(500);                   // 0.5秒待つ
}
