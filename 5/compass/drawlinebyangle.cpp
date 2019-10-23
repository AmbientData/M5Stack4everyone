#include <M5Stack.h>

void drawLineByAngle(int16_t x, int16_t y, int16_t start, int16_t length, int16_t angle, int thick, uint16_t color) {
    float x0 = x + start * sin(radians(angle));
    float y0 = y - start * cos(radians(angle));
    float x1 = x + (start + length) * sin(radians(angle));
    float y1 = y - (start + length) * cos(radians(angle));
    for (int i = 0; i < thick; i++) {
        M5.Lcd.drawLine(x0, y0 - i, x1, y1 - i, color);
    }
}
