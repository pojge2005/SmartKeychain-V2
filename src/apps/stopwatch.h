#pragma once

#include <Arduino.h>

enum class StopwatchState {
    STOPPED,
    RUNNING,
    PAUSED
};

class Stopwatch {
public:
    void begin();
    void update();

    void start();
    void pause();
    void reset();

    StopwatchState state() const;
    uint32_t elapsedSeconds() const;

private:
    StopwatchState currentState = StopwatchState::STOPPED;

    uint32_t elapsed = 0;
    uint32_t lastTickMs = 0;
};

extern Stopwatch stopwatchApp;
