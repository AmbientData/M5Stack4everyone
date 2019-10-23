#ifndef SG90_H
#define SG90_H

class SG90 {
public:
    SG90(void) {};
    virtual ~SG90(void) {};
    void begin(int pin, int ch);
    void write(int angle); // from -90 to +90
private:
    int _ch;  // チャネル番号
    const int _min = 26;  // (26/1024)*20ms ≒ 0.5 ms  (-90°)
    const int _max = 123; // (123/1024)*20ms ≒ 2.4 ms (+90°)
};

#endif // SG90_H
