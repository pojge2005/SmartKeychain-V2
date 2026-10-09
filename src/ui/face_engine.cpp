#include "face_engine.h"

FaceEngine face;

void FaceEngine::begin() {
    current = FaceState::NORMAL;
    frame = 0;
    lastFrameMs = millis();
}

void FaceEngine::update() {
    updateAnimation();
}

void FaceEngine::setFace(FaceState state) {
    if (current == state) {
        return;
    }

    current = state;
    frame = 0;
    lastFrameMs = millis();

    Serial.print("[FACE] ");
    Serial.println(stateName());
}

void FaceEngine::reset() {
    setFace(FaceState::NORMAL);
}

FaceState FaceEngine::state() const {
    return current;
}

const char* FaceEngine::stateName() const {
    switch (current) {
        case FaceState::NORMAL:       return "NORMAL";
        case FaceState::HAPPY:        return "HAPPY";
        case FaceState::SAD:          return "SAD";
        case FaceState::ANGRY:        return "ANGRY";
        case FaceState::SLEEPY:       return "SLEEPY";
        case FaceState::SURPRISED:    return "SURPRISED";
        case FaceState::EXCITED:      return "EXCITED";
        case FaceState::CONFUSED:     return "CONFUSED";
        case FaceState::LOVE:         return "LOVE";
        case FaceState::TIRED:        return "TIRED";
        case FaceState::CHARGING:     return "CHARGING";
        case FaceState::LOW_BATTERY:  return "LOW BATTERY";
        case FaceState::ERROR:        return "ERROR";
        case FaceState::OTA:          return "OTA";
        case FaceState::ALARM:        return "ALARM";
        default:                      return "UNKNOWN";
    }
}

bool FaceEngine::animationActive() const {
    switch (current) {
        case FaceState::NORMAL:
        case FaceState::SLEEPY:
        case FaceState::CHARGING:
        case FaceState::OTA:
        case FaceState::ALARM:
            return true;

        default:
            return false;
    }
}

uint8_t FaceEngine::animationFrame() const {
    return frame;
}

void FaceEngine::updateAnimation() {
    if (!animationActive()) {
        return;
    }

    const uint32_t now = millis();

    if (now - lastFrameMs < FRAME_INTERVAL_MS) {
        return;
    }

    lastFrameMs = now;

    frame++;

    if (frame >= 4) {
        frame = 0;
    }
}
