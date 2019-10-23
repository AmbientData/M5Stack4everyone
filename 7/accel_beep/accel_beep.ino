#include <M5StickC.h>

int16_t offset[3];

const int speaker_pin = 26;
int ledChannel = 0;

// timeoutミリ秒間、加速度生データを取得し、オフセット値を計算
void calibrate(uint32_t timeout) {
    int16_t minX, maxX, minY, maxY, minZ, maxZ, X, Y, Z;
    M5.IMU.getAccelAdc(&minX, &minY, &minZ);
    maxX = minX; maxY = minY; maxZ = minZ;
    uint32_t start = millis();
    while ((millis() - start) < timeout) {
        M5.IMU.getAccelAdc(&X, &Y, &Z);
        maxX = max(maxX, X); minX = min(minX, X);
        maxY = max(maxY, Y); minY = min(minY, Y);
        maxZ = max(maxZ, Z); minZ = min(minZ, Z);
        delay(10);
    }
    offset[0] = minX + (maxX - minX) / 2;
    offset[1] = minY + (maxY - minY) / 2;
    offset[2] = minZ + (maxZ - minZ) / 2;
}

void setup() {
    M5.begin();
    M5.Lcd.setRotation(3);
    M5.Lcd.setCursor(0, 0, 2);
    M5.IMU.Init();
    M5.Lcd.print(M5.IMU.imuType);
    delay(200);
    calibrate(200);

    ledcSetup(ledChannel, 50, 10);  // PWMチャネルを初期設定する
    ledcAttachPin(speaker_pin, ledChannel);  // PWMチャネルにピンを割り当てる
}

void loop() {
    int16_t acc[3];  // x、y、z軸の加速度生データを入れる配列

    M5.IMU.getAccelAdc(&acc[0], &acc[1], &acc[2]);
    M5.Lcd.fillRect(0, 0, 160, 14, BLACK);
    M5.Lcd.setCursor(0, 20);
    float x = (acc[0] - offset[0]) * M5.IMU.aRes;
    float y = (acc[1] - offset[1]) * M5.IMU.aRes;
    float z = (acc[2] - offset[2]) * M5.IMU.aRes + 1;
    M5.Lcd.printf("%.2f %.2f %.2f", x, y, z);
    float diff = sqrt(x * x + y * y);

    ledcWriteTone(ledChannel, 1250);  // 指定した周波数のPWM信号を出す
    delay(50);
    ledcWriteTone(ledChannel, 0);
    int t = ((float)map(constrain(diff * 100, 0, 100), 0, 100, 100, 0) / 100.0) * 1000;
    delay(t);
}
