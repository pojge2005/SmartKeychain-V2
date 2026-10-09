#include "buttons.h"

Buttons buttons;

void Buttons::begin() {
    for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
        pinMode(pins[i], INPUT_PULLUP);

        stableState[i] = digitalRead(pins[i]);
        lastReading[i] = stableState[i];
        lastChangeMs[i] = millis();
    }
}

SystemEvent Buttons::update() {
    const uint32_t now = millis();

    for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
        const bool reading = digitalRead(pins[i]);

        if (reading != lastReading[i]) {
            lastReading[i] = reading;
            lastChangeMs[i] = now;
        }

        if ((now - lastChangeMs[i]) < DEBOUNCE_MS) {
            continue;
        }

        if (reading == stableState[i]) {
            if (!reading && !longSent[i] &&
                (now - pressStartMs[i]) >= LONG_PRESS_MS) {

                longSent[i] = true;
                return longPressEvent(i);
            }

            continue;
        }

        stableState[i] = reading;

        if (!reading) {
            pressStartMs[i] = now;
            longSent[i] = false;
        } else {
            if (!longSent[i]) {
                return shortPressEvent(i);
            }
        }
    }

    return SystemEvent::NONE;
}

SystemEvent Buttons::shortPressEvent(uint8_t index) const {
    switch (index) {
        case 0: return SystemEvent::BUTTON_1;
        case 1: return SystemEvent::BUTTON_2;
        case 2: return SystemEvent::BUTTON_3;
        case 3: return SystemEvent::BUTTON_4;
        default: return SystemEvent::NONE;
    }
}

SystemEvent Buttons::longPressEvent(uint8_t index) const {
    switch (index) {
        case 0: return SystemEvent::BUTTON_1_LONG;
        case 1: return SystemEvent::BUTTON_2_LONG;
        case 2: return SystemEvent::BUTTON_3_LONG;
        case 3: return SystemEvent::BUTTON_4_LONG;
        default: return SystemEvent::NONE;
    }
}