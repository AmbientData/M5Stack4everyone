#include <M5Stack.h>

void setup(){
    M5.begin();
}

void loop(){
    M5.update();  // ボタンを使う時は、定期的に update() を呼ぶ
    if (M5.BtnA.wasPressed()) {        // ボタンAが押されていたら、
        M5.Speaker.tone(261.63, 200);  // ドの音を0.2秒鳴らす
    }
    if (M5.BtnB.wasPressed()) {        // ボタンBが押されていたら、
        M5.Speaker.tone(329.63, 200);  // ミの音を0.2秒鳴らす
    }
    if (M5.BtnC.wasPressed()) {        // ボタンCが押されていたら、
        M5.Speaker.tone(392.00, 200);  // ソの音を0.2秒鳴らす
    }
}
