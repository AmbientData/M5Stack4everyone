#include <M5Stack.h>

void setup(){
    M5.begin();
    M5.Lcd.drawJpgFile(SD, "/cat.jpg", 0, 0);
}

void loop(){

}
