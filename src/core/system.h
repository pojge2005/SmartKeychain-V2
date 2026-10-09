#pragma once

#include <Arduino.h>

enum class SystemState {
    BOOT,
    ACTIVE,
    IDLE,
    DISPLAY_OFF,
    SLEEP,
    CHARGING,
    LOW_BATTERY,
    ERROR
};

class SystemManager {
public:
    void begin();
    void update();

    SystemState state() const;
    void setState(SystemState newState);

    uint32_t uptimeMs() const;

private:
    SystemState currentState = SystemState::BOOT;
    uint32_t bootTime = 0;
};

extern SystemManager systemManager;