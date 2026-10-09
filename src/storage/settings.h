#pragma once

#include <Arduino.h>

struct SettingsData {
    uint8_t brightness = 100;

    uint32_t screenTimeoutMs = 30000;
    uint32_t sleepTimeoutMs = 120000;

    bool soundEnabled = true;
    bool format24Hour = true;

    uint8_t alarmHour = 7;
    uint8_t alarmMinute = 0;
    bool alarmEnabled = false;

    uint8_t batteryLowPercent = 20;
    uint8_t batteryCriticalPercent = 5;

    bool buttonLock = false;
};

class Settings {
public:
    bool begin();

    const SettingsData& data() const;

    bool save();
    void resetDefaults();

    void setBrightness(uint8_t value);
    void setScreenTimeout(uint32_t value);
    void setSleepTimeout(uint32_t value);

    void setSoundEnabled(bool enabled);
    void set24Hour(bool enabled);

    void setAlarm(uint8_t hour, uint8_t minute, bool enabled);

    void setBatteryThresholds(
        uint8_t lowPercent,
        uint8_t criticalPercent
    );

    void setButtonLock(bool locked);

private:
    SettingsData values;
    bool initialized = false;

    bool validate() const;
};

extern Settings settings;