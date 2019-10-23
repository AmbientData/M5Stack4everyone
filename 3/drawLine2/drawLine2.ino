#include <M5Stack.h>

void setup() {
    M5.begin();  // M5Stackオブジェクトを初期化する
}

void loop() {
    M5.Lcd.fillScreen(BLACK);
    for (int y = 0; y < 240; y += 10) {
        M5.Lcd.drawLine(0, 0, 319, y, WHITE);
        delay(50);
    }
    for (int x = 319; x >= 0; x -= 10) {
        M5.Lcd.drawLine(0, 0, x, 239, RED);
        delay(50);
    }
    for (int x = 319; x >= 0; x -= 10) {
        M5.Lcd.drawLine(319, 0, x, 239, BLUE);
        delay(50);
    }
    for (int y = 239; y >= 0; y -= 10) {
        M5.Lcd.drawLine(319, 0, 0, y, GREEN);
        delay(50);
    }
}
