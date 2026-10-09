#include "timer.h"

Timer timerApp;

void Timer::begin() {
    currentState = TimerState::STOPPED;
    remaining = 0;
    lastTickMs = millis();
}

void Timer::update() {
    if (currentState != TimerState::RUNNING) {
        return;
    }

    const uint32_t now = millis();

    while (now - lastTickMs >= 1000) {
        lastTickMs += 1000;

        if (remaining > 0) {
            remaining--;
        }

        if (remaining == 0) {
            complete();
            return;
        }
    }
}

bool Timer::start(uint32_t durationSeconds) {
    if (durationSeconds == 0) {
        return false;
    }

    remaining = durationSeconds;
    currentState = TimerState::RUNNING;
    lastTickMs = millis();

    return true;
}

void Timer::pause() {
    if (currentState == TimerState::RUNNING) {
        currentState = TimerState::PAUSED;
    }
}

void Timer::resume() {
    if (currentState == TimerState::PAUSED && remaining > 0) {
        currentState = TimerState::RUNNING;
        lastTickMs = millis();
    }
}

void Timer::stop() {
    currentState = TimerState::STOPPED;
    remaining = 0;
}

TimerState Timer::state() const {
    return currentState;
}

uint32_t Timer::remainingSeconds() const {
    return remaining;
}

void Timer::complete() {
    currentState = TimerState::COMPLETE;
    remaining = 0;
}
