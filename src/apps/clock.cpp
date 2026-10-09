#include "clock.h"

Clock clockApp;

void Clock::begin() {
    lastTickMs = millis();
    elapsedSeconds = 0;
}

void Clock::update() {
    const uint32_t nowMs = millis();

    while (nowMs - lastTickMs >= 1000) {
        lastTickMs += 1000;

        tickSecond();
        elapsedSeconds++;
    }
}

void Clock::setTime(uint8_t hour, uint8_t minute, uint8_t second) {
    if (hour > 23 || minute > 59 || second > 59) {
        return;
    }

    current.hour = hour;
    current.minute = minute;
    current.second = second;

    lastTickMs = millis();
}

void Clock::setDate(uint16_t year, uint8_t month, uint8_t day) {
    if (year < 2000 || month < 1 || month > 12) {
        return;
    }

    if (day < 1 || day > daysInMonth(year, month)) {
        return;
    }

    current.year = year;
    current.month = month;
    current.day = day;
}

void Clock::set24Hour(bool enabled) {
    format24Hour = enabled;
}

bool Clock::is24Hour() const {
    return format24Hour;
}

const DateTime& Clock::now() const {
    return current;
}

uint32_t Clock::uptimeSeconds() const {
    return elapsedSeconds;
}

void Clock::tickSecond() {
    current.second++;

    if (current.second >= 60) {
        current.second = 0;
        tickMinute();
    }
}

void Clock::tickMinute() {
    current.minute++;

    if (current.minute >= 60) {
        current.minute = 0;
        tickHour();
    }
}

void Clock::tickHour() {
    current.hour++;

    if (current.hour >= 24) {
        current.hour = 0;
        tickDay();
    }
}

void Clock::tickDay() {
    current.day++;

    current.dayOfWeek++;

    if (current.dayOfWeek >= 7) {
        current.dayOfWeek = 0;
    }

    if (current.day > daysInMonth(current.year, current.month)) {
        current.day = 1;
        current.month++;

        if (current.month > 12) {
            current.month = 1;
            current.year++;
        }
    }
}

uint8_t Clock::daysInMonth(uint16_t year, uint8_t month) const {
    switch (month) {
        case 2:
            return isLeapYear(year) ? 29 : 28;

        case 4:
        case 6:
        case 9:
        case 11:
            return 30;

        default:
            return 31;
    }
}

bool Clock::isLeapYear(uint16_t year) const {
    return ((year % 4 == 0 && year % 100 != 0) ||
            (year % 400 == 0));
}
