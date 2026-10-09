#pragma once

#include <Arduino.h>

class Alarm {
public:
    void begin();
    void update();

    void set(uint8_t hour, uint8_t minute);
    void enable();
    void disable();

    bool enabled() const;
    bool triggered() const;

    void clearTrigger();

private:
    uint8_t alarmHour = 7;
    uint8_t alarmMinute = 0;

    bool alarmEnabled = false;
    bool alarmTriggered = false;

    uint32_t lastCheckMs = 0;
    uint32_t lastTriggerMinute = UINT32_MAX;
};

extern Alarm alarmApp;
