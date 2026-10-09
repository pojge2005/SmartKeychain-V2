#pragma once

#include <Arduino.h>

struct DateTime {
    uint16_t year;
    uint8_t month;
    uint8_t day;

    uint8_t hour;
    uint8_t minute;
    uint8_t second;

    uint8_t dayOfWeek;
};

class Clock {
public:
    void begin();
    void update();

    void setTime(uint8_t hour, uint8_t minute, uint8_t second);
    void setDate(uint16_t year, uint8_t month, uint8_t day);

    void set24Hour(bool enabled);
    bool is24Hour() const;

    const DateTime& now() const;
    uint32_t uptimeSeconds() const;

private:
    DateTime current{
        2026, 1, 1,
        0, 0, 0,
        4
    };

    bool format24Hour = true;

    uint32_t lastTickMs = 0;
    uint32_t elapsedSeconds = 0;

    void tickSecond();
    void tickMinute();
    void tickHour();
    void tickDay();

    uint8_t daysInMonth(uint16_t year, uint8_t month) const;
    bool isLeapYear(uint16_t year) const;
};

extern Clock clockApp;
