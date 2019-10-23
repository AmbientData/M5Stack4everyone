#include <M5Stack.h>
#include <Avatar.h>  // アバターライブラリを使う時は Avatar.h をインクルードする

using namespace m5avatar;

Avatar avatar;  // Avatarクラスの変数（オブジェクト）を定義

void setup() {
    M5.begin();

    avatar.init();  // avatarオブジェクトを初期化する
}

void loop() {
    M5.update();  // ボタンを使う時は、定期的に update() を呼ぶ  ----④
    if (M5.BtnA.wasPressed()) {                     // ボタンAが押されていたら、  ----⑤
        avatar.setExpression(Expression::Neutral);  // アバターの表情を「普通」にする  ----⑥
    }
    if (M5.BtnB.wasPressed()) {                     // ボタンBが押されていたら、
        avatar.setExpression(Expression::Happy);    // アバターの表情を「幸せ」にする
    }
    if (M5.BtnB.pressedFor(1000)) {                 // ボタンBが1秒以上長押しされていたら、  ----⑦
        avatar.setExpression(Expression::Neutral);  // アバターの表情を「普通」にする
    }
    if (M5.BtnC.wasPressed()) {                     // ボタンCが押されていたら、
        avatar.setExpression(Expression::Angry);    // アバターの表情を「怒り」にする
    }
    if (M5.BtnC.pressedFor(1000)) {                 // ボタンCが1秒以上長押しされていたら、
        avatar.setExpression(Expression::Neutral);  // アバターの表情を「普通」にする
    }
}
