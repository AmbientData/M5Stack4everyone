#include <M5Stack.h>

#define SPEAKER_PIN 25

void setup(){
    M5.begin();
}

void beep(int freq, int duration, uint8_t volume) {  // freq(Hz), duration(ms), volume(1〜255)
    int t = 1000000 / freq / 2;
    unsigned long start = millis();
    while ((millis() - start) < duration) {
        dacWrite(SPEAKER_PIN, 0);
        delayMicroseconds(t);
        dacWrite(SPEAKER_PIN, volume); 
        delayMicroseconds(t);
    }
    dacWrite(SPEAKER_PIN, 0);
}

void loop(){
    M5.update();  // ボタンを使う時は、定期的に update() を呼ぶ
    if (M5.BtnA.wasPressed()) {  // ボタンAが押されていたら、
        beep(440, 1000, 2);      // 440Hzの音を1秒鳴らす
    }
}
