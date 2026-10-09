#include "stopwatch.h"

Stopwatch stopwatchApp;

void Stopwatch::begin() {
    currentState = StopwatchState::STOPPED;
    elapsed = 0;
    lastTickMs = millis();
}

void Stopwatch::update() {
    if (currentState != StopwatchState::RUNNING) {
        return;
    }

    const uint32_t now = millis();

    while (now - lastTickMs >= 1000) {
        lastTickMs += 1000;
        elapsed++;
    }
}

void Stopwatch::start() {
    if (currentState != StopwatchState::RUNNING) {
        currentState = StopwatchState::RUNNING;
        lastTickMs = millis();
    }
}

void Stopwatch::pause() {
    if (currentState == StopwatchState::RUNNING) {
        currentState = StopwatchState::PAUSED;
    }
}

void Stopwatch::reset() {
    currentState = StopwatchState::STOPPED;
    elapsed = 0;
    lastTickMs = millis();
}

StopwatchState Stopwatch::state() const {
    return currentState;
}

uint32_t Stopwatch::elapsedSeconds() const {
    return elapsed;
}
