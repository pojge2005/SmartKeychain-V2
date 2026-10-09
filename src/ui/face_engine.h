#pragma once

#include <Arduino.h>

enum class FaceState {
    NORMAL,
    HAPPY,
    SAD,
    ANGRY,
    SLEEPY,
    SURPRISED,
    EXCITED,
    CONFUSED,
    LOVE,
    TIRED,
    CHARGING,
    LOW_BATTERY,
    ERROR,
    OTA,
    ALARM
};

class FaceEngine {
public:
    void begin();
    void update();

    void setFace(FaceState state);
    void reset();

    FaceState state() const;
    const char* stateName() const;

    bool animationActive() const;
    uint8_t animationFrame() const;

private:
    FaceState current = FaceState::NORMAL;

    uint8_t frame = 0;
    uint32_t lastFrameMs = 0;

    static constexpr uint32_t FRAME_INTERVAL_MS = 120;

    void updateAnimation();
};

extern FaceEngine face;
