#include "rgb.h"
#include "config.h"
#include <Arduino.h>

Rgb rgb;

void Rgb::begin() {
    pinMode(RGB_RED_PIN, OUTPUT);
    pinMode(RGB_GREEN_PIN, OUTPUT);
    pinMode(RGB_BLUE_PIN, OUTPUT);

    off();
}

void Rgb::write(bool red, bool green, bool blue) {
    if (RGB_COMMON_ANODE) {
        digitalWrite(RGB_RED_PIN, !red);
        digitalWrite(RGB_GREEN_PIN, !green);
        digitalWrite(RGB_BLUE_PIN, !blue);
    } else {
        digitalWrite(RGB_RED_PIN, red);
        digitalWrite(RGB_GREEN_PIN, green);
        digitalWrite(RGB_BLUE_PIN, blue);
    }
}

void Rgb::off() {
    write(false, false, false);
}

void Rgb::red() {
    write(true, false, false);
}

void Rgb::green() {
    write(false, true, false);
}

void Rgb::blue() {
    write(false, false, true);
}

void Rgb::white() {
    write(true, true, true);
}
