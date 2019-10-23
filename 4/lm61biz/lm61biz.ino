#include <M5Stack.h>

#define LM61BIZ_PIN 35  // LM61BIZを35番ピンのAD変換器につなぐ

void setup() {
    M5.begin();  // M5Stackを初期化する
    pinMode(LM61BIZ_PIN, INPUT);  // 35番ピンを入力モードに設定する

    M5.Lcd.setTextSize(4);
}

void loop() {
    int e = analogRead(LM61BIZ_PIN);         // 35番ピンの電圧値を読む

    float Vout = e / 4095.0 * 3.3 + 0.1132;  // 電圧を計算する
    float temp = (Vout - 0.6) / 0.01;        // 電圧を温度に変換する
    M5.Lcd.setCursor(80, 100);
    M5.Lcd.print(temp, 1);                   // 温度をLCDに書く
    M5.Lcd.print("'C");
    delay(1000);
}
