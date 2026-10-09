#include "alarm.h"
#include "clock.h"

Alarm alarmApp;

void Alarm::begin() {
    lastCheckMs = millis();
    lastTriggerMinute = UINT32_MAX;
}

void Alarm::update() {
    if (!alarmEnabled) {
        return;
    }

    const uint32_t nowMs = millis();

    if (nowMs - lastCheckMs < 500) {
        return;
    }

    lastCheckMs = nowMs;

    const DateTime& now = clockApp.now();

    if (now.hour != alarmHour || now.minute != alarmMinute) {
        return;
    }

    const uint32_t minuteId =
        (static_cast<uint32_t>(now.year) * 525600UL) +
        (static_cast<uint32_t>(now.month) * 44640UL) +
        (static_cast<uint32_t>(now.day) * 1440UL) +
        (static_cast<uint32_t>(now.hour) * 60UL) +
        now.minute;

    if (minuteId == lastTriggerMinute) {
        return;
    }

    lastTriggerMinute = minuteId;
    alarmTriggered = true;
}

void Alarm::set(uint8_t hour, uint8_t minute) {
    if (hour > 23 || minute > 59) {
        return;
    }

    alarmHour = hour;
    alarmMinute = minute;
    alarmTriggered = false;
}

void Alarm::enable() {
    alarmEnabled = true;
    alarmTriggered = false;
}

void Alarm::disable() {
    alarmEnabled = false;
    alarmTriggered = false;
}

bool Alarm::enabled() const {
    return alarmEnabled;
}

bool Alarm::triggered() const {
    return alarmTriggered;
}

void Alarm::clearTrigger() {
    alarmTriggered = false;
}