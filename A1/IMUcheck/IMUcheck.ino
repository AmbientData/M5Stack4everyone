#include <M5Stack.h>
#include <Wire.h>

#define MPU9250_ADDRESS 0x68  // I2Cアドレス。MPU6886と共通
#define WHO_AM_I_MPU9250   0x75 // MPU6886と共通

void setup() {
    unsigned char whoami;

    M5.begin();
    M5.Lcd.setCursor(20, 40);
    M5.Lcd.setTextSize(2);

    Wire.begin();
    Wire.beginTransmission(MPU9250_ADDRESS);
    Wire.write(WHO_AM_I_MPU9250);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU9250_ADDRESS, 1);
    whoami = Wire.read();

    if (whoami == 0x71) {
        M5.Lcd.print("MPU9250 inside");
    } else if (whoami == 0x19) {
        M5.Lcd.print("MPU6886 inside");
    } else {
        M5.Lcd.print("unknown device");
    }
    M5.Lcd.printf(" (%02x)", whoami);
}

void loop() {
}
