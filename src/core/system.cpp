#include "system.h"

SystemManager systemManager;

void SystemManager::begin() {
    bootTime = millis();
    currentState = SystemState::ACTIVE;
}

void SystemManager::update() {
    // Core system processing will be added here.
}

SystemState SystemManager::state() const {
    return currentState;
}

void SystemManager::setState(SystemState newState) {
    if (currentState == newState) {
        return;
    }

    currentState = newState;
}

uint32_t SystemManager::uptimeMs() const {
    return millis() - bootTime;
}