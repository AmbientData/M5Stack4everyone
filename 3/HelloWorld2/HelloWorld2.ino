#include <M5Stack.h>

void setup() {
    M5.begin();  // M5Stackオブジェクトを初期化する

    M5.Lcd.setCursor(40, 60);  // 文字を書く位置を設定する
    M5.Lcd.setTextSize(3);     // 文字サイズを設定する
    M5.Lcd.print("Hello World ");
}

void loop() {

}
