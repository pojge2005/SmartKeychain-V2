#include "oled.h"
#include "config.h"
#include <Wire.h>

Oled oled;

bool Oled::begin() {
    Wire.begin(OLED_SDA, OLED_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        return false;
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("SmartKeychain");
    display.println("V2.1 / B3");
    display.display();

    return true;
}

void Oled::clear() {
    display.clearDisplay();
    display.display();
}

void Oled::showBoot() {
    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("SMART");

    display.setCursor(0, 22);
    display.println("KEYCHAIN");

    display.setTextSize(1);
    display.setCursor(0, 48);
    display.println("V2.1 / B3");

    display.display();
}

void Oled::showHardwareTest() {
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("B3 HARDWARE TEST");

    display.println();
    display.println("OLED       OK");
    display.println("I2C        OK");
    display.println("SYSTEM     OK");

    display.display();
}
