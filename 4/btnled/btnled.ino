#include <M5Stack.h>

#define LED_PIN 2

void setup(){
    M5.begin();
    pinMode(LED_PIN, OUTPUT);  // GPIO2を出力モードに設定する
}

int led = HIGH;  // LEDの状態を示す変数

void loop(){
    M5.update();
    if (M5.BtnA.wasPressed()) {  // ボタンAが押されていたら、
        led = HIGH;              // LED状態をHIGHにする
    }
    if (M5.BtnB.wasPressed()) {  // ボタンBが押されていたら、
        led = LOW;               // LED状態をLOWにする
    }
    if (M5.BtnC.wasPressed()) {  // ボタンCが押されていたら、
        led = (led == HIGH) ? LOW : HIGH;  // LED状態をHIGH／LOW入れ替える
    }
    digitalWrite(LED_PIN, led);  // LED状態を書き込む
    delay(50);
}
