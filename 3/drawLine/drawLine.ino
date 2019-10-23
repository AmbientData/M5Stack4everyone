#include <M5Stack.h>

void setup() {
    M5.begin();  // M5Stackオブジェクトを初期化する
    M5.Lcd.drawLine(0, 0, 319, 239, WHITE); // LCDに線を描く
}

void loop() {

}
