#include <M5Stack.h>

#include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();  // Adafruit_Si7021オブジェクトを初期化する

const int R = 266;
const int Xt = 286;  // 温度計の針の中心座標
const int Yt = 225;
const int Xh = 34;  // 湿度計の針の中心座標
const int Yh = 225;

void drawLineByAngle(int16_t x, int16_t y, int16_t start, int16_t length,
    int16_t angle, int thick, uint16_t color);

void drawScale() {
    M5.Lcd.setCursor(35, 10);
    M5.Lcd.print("temp('C)");
    for (int i = -10; i <= 40; i++) {
        int l1 = (i % 10) ? 5 : 10;
        drawLineByAngle(Xt, Yt, R - l1, l1, map(i, -10, 40, 270, (270 + 50)), 1, BLACK);
        if (i % 20 == 0) {
            int a = map(i, -10, 40, 0, 50);
            M5.Lcd.setCursor(Xt - R * cos(radians(a)) - 15, 220 - R * sin(radians(a)));
            M5.Lcd.print(i);
        }
    }
    M5.Lcd.setCursor(240, 10);
    M5.Lcd.print("humid(%)");
    for (int i = 0; i <= 100; i += 2) {
        int l1 = (i % 10) ? 5 : 10;
        drawLineByAngle(Xh, Yh, R - l1, l1, map(i, 0, 100, 90, (90 - 50)), 1, BLACK);
        if (i % 20 == 0) {
            int a = map(i, 0, 100, 0, 50);
            M5.Lcd.setCursor(R * cos(radians(a)) + Xh + 5, 220 - R * sin(radians(a)));
            M5.Lcd.print(i);
        }
    }
}

void setup() {
    M5.begin();  // M5Stackを初期化する
    Serial.begin(115200);
    while (!Serial) ;

    if (!sensor.begin()) {  // Si7021を初期化する
        Serial.println("Did not find Si7021 sensor!");
        while (true) ;
    }

    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(BLACK, WHITE);

    drawScale();
}

float oldtemp = 0;
float oldhumid = 0;

void loop() {
    float temp = sensor.readTemperature();   // Si7021から温度を読む
    float humid = sensor.readHumidity();     // Si7021から湿度を読む

    drawLineByAngle(Xt, Yt, 0, R - 12, map(oldtemp, -10, 40, 270, (270 + 50)), 2, WHITE);  // 古い針を消す
    drawLineByAngle(Xh, Yh, 0, R - 12, map(oldhumid, 0, 100, 90, (90 - 50)), 2, WHITE);

    drawLineByAngle(Xt, Yt, 0, R - 12, map(temp, -10, 40, 270, (270 + 50)), 2, BLACK);  // 新しい針を描く
    drawLineByAngle(Xh, Yh, 0, R - 12, map(humid, 0, 100, 90, (90 - 50)), 2, BLACK);

    M5.Lcd.fillCircle(Xt, Yt, 4, BLACK);
    M5.Lcd.fillCircle(Xh, Yh, 4, BLACK);

    oldtemp = temp;
    oldhumid = humid;

    delay(1000);
}
