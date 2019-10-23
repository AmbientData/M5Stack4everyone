#include <M5Stack.h>
#include <Wire.h>

float ncirtemperature();

void setup() {
    M5.begin();
    Wire.begin();

    M5.Lcd.setTextSize(3);
    M5.Lcd.fillScreen(BLACK);
}

void loop() {
    float temperature = ncirtemperature();

    M5.Lcd.fillRect(120,100,120,100,BLACK);
    M5.Lcd.setCursor(120, 100);
    M5.Lcd.print(temperature);

    delay(500);
}
