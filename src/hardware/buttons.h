#pragma once

#include <Arduino.h>
#include "config.h"
#include "core/events.h"

class Buttons {
public:
    void begin();
    SystemEvent update();

private:
    static constexpr uint8_t BUTTON_COUNT = 4;
    static constexpr uint32_t DEBOUNCE_MS = 30;
    static constexpr uint32_t LONG_PRESS_MS = 700;

    const uint8_t pins[BUTTON_COUNT] = {
        BUTTON_1_PIN,
        BUTTON_2_PIN,
        BUTTON_3_PIN,
        BUTTON_4_PIN
    };

    bool stableState[BUTTON_COUNT] = {true, true, true, true};
    bool lastReading[BUTTON_COUNT] = {true, true, true, true};
    bool longSent[BUTTON_COUNT] = {false, false, false, false};

    uint32_t lastChangeMs[BUTTON_COUNT] = {0, 0, 0, 0};
    uint32_t pressStartMs[BUTTON_COUNT] = {0, 0, 0, 0};

    SystemEvent shortPressEvent(uint8_t index) const;
    SystemEvent longPressEvent(uint8_t index) const;
};

extern Buttons buttons;