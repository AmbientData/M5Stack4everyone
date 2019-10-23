#include <M5Stack.h>

#define DAC 26

void setup() {
    M5.begin();  // M5Stackを初期化する
}

void loop() {
    for (int i = 0; i < 256; i += 10) {
        dacWrite(DAC, i);  // 26番ピンにアナログ電圧を出力する
        delay(100);
    }
}
