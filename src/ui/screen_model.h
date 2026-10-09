#pragma once

#include <Arduino.h>
#include "ui.h"
#include "face_engine.h"

struct HomeScreenData {
    uint16_t year = 2026;

    uint8_t month = 1;
    uint8_t day = 1;
    uint8_t dayOfWeek = 0;

    uint8_t hour = 0;
    uint8_t minute = 0;
    uint8_t second = 0;

    uint8_t batteryPercent = 100;

    bool charging = false;
    bool alarmActive = false;
    bool wifiConnected = false;
    bool bleConnected = false;

    FaceState face = FaceState::NORMAL;
};


struct MenuItem {
    const char* title;
    Screen screen;
};
