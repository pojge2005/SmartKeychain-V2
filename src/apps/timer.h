#pragma once

#include <Arduino.h>

enum class TimerState {
    STOPPED,
    RUNNING,
    PAUSED,
    COMPLETE
};

class Timer {
public:
    void begin();
    void update();

    bool start(uint32_t durationSeconds);
    void pause();
    void resume();
    void stop();

    TimerState state() const;
    uint32_t remainingSeconds() const;

private:
    TimerState currentState = TimerState::STOPPED;

    uint32_t remaining = 0;
    uint32_t lastTickMs = 0;

    void complete();
};
extern Timer timerApp;