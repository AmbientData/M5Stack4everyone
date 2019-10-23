#include <M5Stack.h>

void setup() {
    M5.begin();  // M5Stackオブジェクトを初期化する

    M5.Lcd.fillRect(120, 140, 80, 30, WHITE);  // 四角を塗りつぶす
    M5.Lcd.fillCircle(90, 80, 10, WHITE);      // 円を塗りつぶす
    M5.Lcd.fillCircle(230, 80, 10, WHITE);     // 円を塗りつぶす
}

void loop() {

}
