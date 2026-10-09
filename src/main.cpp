#include <Arduino.h>

#include "config.h"
#include "core/system.h"
#include "core/events.h"
#include "hardware/buttons.h"
#include "ui/ui.h"
#include "ui/face_engine.h"
#include "apps/clock.h"
#include "apps/timer.h"
#include "apps/stopwatch.h"
#include "apps/alarm.h"
#include "storage/settings.h"
#include "apps/games/game_center.h"
#include "storage/high_scores.h"
#include "apps/games/snake.h"

static void handleEvent(SystemEvent event)
{
    if (gameCenter.active()) {

        switch (event) {
            case SystemEvent::BUTTON_1:
                gameCenter.button1();
                return;

            case SystemEvent::BUTTON_2:
                gameCenter.button2();
                return;

            case SystemEvent::BUTTON_3:
                gameCenter.button3();
                return;

            case SystemEvent::BUTTON_4:
                gameCenter.button4();
                return;

            case SystemEvent::BUTTON_4_LONG:
                Serial.println("[UI] Game exit requested");
                gameCenter.exit();
                ui.open(Screen::GAMES);
                return;

            default:
                return;
        }
    }

    switch (event) {
        case SystemEvent::BUTTON_1:
            ui.previous();
            face.setFace(FaceState::HAPPY);
            break;

        case SystemEvent::BUTTON_2:
            ui.next();
            face.setFace(FaceState::EXCITED);
            break;

        case SystemEvent::BUTTON_3:
            ui.select();
            face.setFace(FaceState::SURPRISED);
            break;

        case SystemEvent::BUTTON_4:
            ui.back();
            face.setFace(FaceState::NORMAL);
            break;

        case SystemEvent::BUTTON_1_LONG:
            ui.back();
            face.setFace(FaceState::SLEEPY);
            break;

        default:
            break;
    }

}
void setup() {
    Serial.begin(115200);

    delay(200);

    Serial.println();
    Serial.println("==============================");
    Serial.println(" SMART KEYCHAIN");
    Serial.println(" V2.1 / B3");
    Serial.println("==============================");

    buttons.begin();
    systemManager.begin();
    face.begin();
    ui.begin();

    clockApp.begin();
    timerApp.begin();
    stopwatchApp.begin();
    alarmApp.begin();

    snakeGame.begin();
    gameCenter.begin();

    if (!highScores.begin()) {
        Serial.println("HIGH SCORES: FAILED");
    } else {
        Serial.println("HIGH SCORES: READY");
    }

    if (!settings.begin()) {
        Serial.println("SETTINGS: DEFAULTS");
    } else {
        Serial.println("SETTINGS: LOADED");
    }

    clockApp.set24Hour(settings.data().format24Hour);

    alarmApp.set(
        settings.data().alarmHour,
        settings.data().alarmMinute
    );

    if (settings.data().alarmEnabled) {
        alarmApp.enable();
    }

    Serial.println("CORE       : READY");
    Serial.println("BUTTONS    : READY");
    Serial.println("UI         : READY");
    Serial.println("BOOT       : COMPLETE");
}

void loop() {
    systemManager.update();

    clockApp.update();
    timerApp.update();
    stopwatchApp.update();
    alarmApp.update();
    gameCenter.update();
    face.update();

    const SystemEvent event = buttons.update();

    if (event != SystemEvent::NONE) {
        Serial.print("[BUTTON EVENT] ");
        Serial.println(static_cast<int>(event));
        handleEvent(event);
    }

    ui.update();
}