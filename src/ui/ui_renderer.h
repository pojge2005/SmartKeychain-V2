#pragma once

#include <Arduino.h>
#include "ui.h"
#include "face_engine.h"

class UIRenderer {
public:
    bool begin();
    void render(Screen screen);

    void showMessage(const char* title, const char* message);

private:
    void clear();
    void present();

    void drawHome();
    void drawMenu();
    void drawClock();
    void drawBattery();
    void drawKeychain();
    void drawGames();
    void drawTimer();
    void drawStopwatch();
    void drawAlarm();
    void drawSettings();
    void drawDiagnostics();
    void drawAbout();

    void drawActiveGame();

    void drawFace(FaceState state, uint8_t frame);

    void drawStatusBar();
    void drawEyesNormal(uint8_t frame);
    void drawEyesHappy();
    void drawEyesSad();
    void drawEyesAngry();
    void drawEyesSleepy();
    void drawEyesSurprised();
    void drawEyesExcited();
    void drawEyesConfused();
    void drawEyesLove();
    void drawEyesTired();
    void drawEyesCharging();
    void drawEyesLowBattery();
    void drawEyesError();
    void drawEyesOTA();
    void drawEyesAlarm();

    void drawSnake();
    void drawReaction();
    void drawDodge();
    void drawMemory();
};

extern UIRenderer renderer;
