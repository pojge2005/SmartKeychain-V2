#pragma once

#include <Adafruit_SSD1306.h>

class Oled {
public:
    bool begin();
    void clear();
    void showBoot();
    void showHardwareTest();

private:
    Adafruit_SSD1306 display =
        Adafruit_SSD1306(128, 64, &Wire, -1);
};

extern Oled oled;
