#include "battery.h"
#include "config.h"
#include <Arduino.h>

Battery battery;

void Battery::begin() {
    pinMode(BATTERY_ADC_PIN, INPUT);
}

int Battery::readRaw() {
    return analogRead(BATTERY_ADC_PIN);
}
