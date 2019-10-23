#include <M5Stack.h>

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
