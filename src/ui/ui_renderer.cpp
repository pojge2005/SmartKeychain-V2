#include "ui.h"
#include "ui_renderer.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"
#include "apps/clock.h"
#include "apps/games/game_center.h"
#include "apps/games/snake.h"
#include "apps/games/reaction.h"
#include "apps/games/dodge.h"
#include "apps/games/memory.h"

namespace {
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);
}

UIRenderer renderer;

bool UIRenderer::begin()
{
    Wire.begin(OLED_SDA, OLED_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        return false;
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(18, 20);
    display.println("SMART KEYCHAIN");
    display.setCursor(30, 36);
    display.println("Starting...");
    display.display();

    return true;
}

void UIRenderer::clear()
{
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
}

void UIRenderer::present()
{
    display.display();
}

void UIRenderer::showMessage(const char* title, const char* message)
{
    clear();
    display.setCursor(0, 0);
    display.println(title ? title : "");
    display.drawLine(0, 11, 127, 11, SSD1306_WHITE);
    display.setCursor(0, 20);
    display.println(message ? message : "");
    present();
}

void UIRenderer::render(Screen screen)
{
    clear();

    if (gameCenter.active()) {
        drawActiveGame();
        present();
        return;
    }

    if (ui.menuOpen()) {
        drawMenu();
        present();
        return;
    }

    switch (screen) {
        case Screen::HOME:        drawHome(); break;
        case Screen::CLOCK:       drawClock(); break;
        case Screen::BATTERY:     drawBattery(); break;
        case Screen::KEYCHAIN:    drawKeychain(); break;
        case Screen::GAMES:       drawGames(); break;
        case Screen::TIMER:       drawTimer(); break;
        case Screen::STOPWATCH:   drawStopwatch(); break;
        case Screen::ALARM:       drawAlarm(); break;
        case Screen::SETTINGS:    drawSettings(); break;
        case Screen::DIAGNOSTICS: drawDiagnostics(); break;
        case Screen::ABOUT:       drawAbout(); break;
    }

    present();
}

void UIRenderer::drawActiveGame()
{
    switch (gameCenter.currentGame()) {
        case GameId::SNAKE:    drawSnake(); break;
        case GameId::REACTION: drawReaction(); break;
        case GameId::DODGE:    drawDodge(); break;
        case GameId::MEMORY:   drawMemory(); break;
        default:               drawGames(); break;
    }
}

void UIRenderer::drawHome()
{
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("SMART KEYCHAIN");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

    drawFace(face.state(), face.animationFrame());

    display.setTextSize(1);
    display.setCursor(0, 55);
    display.print("B1: Menu  B4: Status");
}

void UIRenderer::drawMenu()
{
    static const char* items[] = {
        "Clock",
        "Game Center",
        "Keychain",
        "Battery",
        "Timer",
        "Stopwatch",
        "Alarm",
        "Settings"
    };

    const uint8_t count = sizeof(items) / sizeof(items[0]);
    const uint8_t selected = ui.menuIndex();

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("MAIN MENU");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

    // Four visible rows; scroll to keep the selected item visible.
    uint8_t first = 0;
    if (selected >= 4) {
        first = selected - 3;
    }

    for (uint8_t row = 0; row < 4; ++row) {
        const uint8_t index = first + row;
        if (index >= count) {
            break;
        }

        const int16_t y = 14 + row * 12;

        if (index == selected) {
            display.fillRect(0, y - 1, 128, 11, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
        } else {
            display.setTextColor(SSD1306_WHITE);
        }

        display.setCursor(4, y);
        display.print(index == selected ? "> " : "  ");
        display.print(items[index]);
    }

    display.setTextColor(SSD1306_WHITE);
}

void UIRenderer::drawClock()
{
    display.setCursor(0, 0);
    display.println("CLOCK");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
    display.setCursor(0, 24);
    display.println("Software clock");
    display.setCursor(0, 40);
    display.println("Set time in settings");
}

void UIRenderer::drawBattery()
{
    display.setCursor(0, 0);
    display.println("BATTERY");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
    display.setCursor(0, 24);
    display.println("Voltage: not calibrated");
    display.setCursor(0, 40);
    display.println("Percentage unavailable");
}

void UIRenderer::drawKeychain()
{
    display.setCursor(0, 0);
    display.println("KEYCHAIN STATUS");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
    display.setCursor(0, 26);
    display.println("Mechanism not configured");
    display.setCursor(0, 42);
    display.println("Hardware test pending");
}

void UIRenderer::drawGames()
{
    display.setCursor(0, 0);
    display.println("GAME CENTER");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
    display.setCursor(4, 16);
    display.println("1. Snake");
    display.setCursor(4, 27);
    display.println("2. Reaction");
    display.setCursor(4, 38);
    display.println("3. Dodge");
    display.setCursor(4, 49);
    display.println("4. Memory");
}

void UIRenderer::drawTimer()
{
    display.setCursor(0, 0);
    display.println("TIMER");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
    display.setCursor(0, 26);
    display.println("Timer interface pending");
}

void UIRenderer::drawStopwatch()
{
    display.setCursor(0, 0);
    display.println("STOPWATCH");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
    display.setCursor(0, 26);
    display.println("Stopwatch interface pending");
}

void UIRenderer::drawAlarm()
{
    display.setCursor(0, 0);
    display.println("ALARM");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
    display.setCursor(0, 26);
    display.println("Alarm interface pending");
}

void UIRenderer::drawSettings()
{
    display.setCursor(0, 0);
    display.println("SETTINGS");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
    display.setCursor(0, 26);
    display.println("Settings interface pending");
}

void UIRenderer::drawDiagnostics()
{
    display.setCursor(0, 0);
    display.println("DIAGNOSTICS");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
    display.setCursor(0, 26);
    display.println("Firmware running");
}

void UIRenderer::drawAbout()
{
    display.setCursor(0, 0);
    display.println("ABOUT");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
    display.setCursor(0, 22);
    display.println("Smart Keychain");
    display.println("ESP32-C3");
    display.println("Firmware V2.1");
}

void UIRenderer::drawFace(FaceState state, uint8_t frame)
{
    const int16_t leftX = 40;
    const int16_t rightX = 88;
    const int16_t eyeY = 32;

    switch (state) {
        case FaceState::HAPPY:
        case FaceState::EXCITED:
            display.fillCircle(leftX, eyeY, 12, SSD1306_WHITE);
            display.fillCircle(rightX, eyeY, 12, SSD1306_WHITE);
            display.fillCircle(leftX, eyeY, 4, SSD1306_BLACK);
            display.fillCircle(rightX, eyeY, 4, SSD1306_BLACK);
            break;

        case FaceState::SAD:
            display.fillRoundRect(27, 31, 26, 10, 4, SSD1306_WHITE);
            display.fillRoundRect(75, 31, 26, 10, 4, SSD1306_WHITE);
            display.drawLine(27, 24, 53, 31, SSD1306_WHITE);
            display.drawLine(75, 31, 101, 24, SSD1306_WHITE);
            break;

        case FaceState::ANGRY:
            display.drawLine(25, 23, 54, 32, SSD1306_WHITE);
            display.drawLine(74, 32, 103, 23, SSD1306_WHITE);
            display.fillRoundRect(28, 33, 25, 10, 3, SSD1306_WHITE);
            display.fillRoundRect(75, 33, 25, 10, 3, SSD1306_WHITE);
            break;

        case FaceState::SLEEPY:
        case FaceState::TIRED:
            display.fillRoundRect(25, 33, 30, 6, 3, SSD1306_WHITE);
            display.fillRoundRect(73, 33, 30, 6, 3, SSD1306_WHITE);
            break;

        case FaceState::SURPRISED:
            display.drawCircle(leftX, eyeY, 12, SSD1306_WHITE);
            display.drawCircle(rightX, eyeY, 12, SSD1306_WHITE);
            display.fillCircle(leftX, eyeY, 4, SSD1306_WHITE);
            display.fillCircle(rightX, eyeY, 4, SSD1306_WHITE);
            break;

        case FaceState::CONFUSED:
            display.fillRoundRect(26, 27, 28, 12, 4, SSD1306_WHITE);
            display.drawCircle(rightX, eyeY, 10, SSD1306_WHITE);
            display.fillCircle(rightX, eyeY, 3, SSD1306_WHITE);
            break;

        case FaceState::LOVE:
            display.fillCircle(35, 29, 8, SSD1306_WHITE);
            display.fillCircle(45, 29, 8, SSD1306_WHITE);
            display.fillTriangle(27, 32, 53, 32, 40, 46, SSD1306_WHITE);
            display.fillCircle(83, 29, 8, SSD1306_WHITE);
            display.fillCircle(93, 29, 8, SSD1306_WHITE);
            display.fillTriangle(75, 32, 101, 32, 88, 46, SSD1306_WHITE);
            break;

        case FaceState::CHARGING:
            display.drawRoundRect(25, 23, 30, 20, 5, SSD1306_WHITE);
            display.drawRoundRect(73, 23, 30, 20, 5, SSD1306_WHITE);
            display.setCursor(35, 29);
            display.print("+");
            display.setCursor(83, 29);
            display.print("+");
            break;

        case FaceState::LOW_BATTERY:
            display.fillRoundRect(25, 32, 30, 7, 3, SSD1306_WHITE);
            display.fillRoundRect(73, 32, 30, 7, 3, SSD1306_WHITE);
            break;

        case FaceState::ERROR:
            display.drawLine(28, 24, 52, 44, SSD1306_WHITE);
            display.drawLine(52, 24, 28, 44, SSD1306_WHITE);
            display.drawLine(76, 24, 100, 44, SSD1306_WHITE);
            display.drawLine(100, 24, 76, 44, SSD1306_WHITE);
            break;

        case FaceState::OTA: {
            const int16_t offset = (millis() / 250) % 2 ? 4 : 0;
            display.fillRoundRect(25 + offset, 27, 30, 13, 4, SSD1306_WHITE);
            display.fillRoundRect(73 + offset, 27, 30, 13, 4, SSD1306_WHITE);
            break;
        }

        case FaceState::ALARM:
            if ((millis() / 250) % 2 == 0) {
                display.fillCircle(leftX, eyeY, 12, SSD1306_WHITE);
                display.fillCircle(rightX, eyeY, 12, SSD1306_WHITE);
            } else {
                display.fillRoundRect(25, 32, 30, 5, 3, SSD1306_WHITE);
                display.fillRoundRect(73, 32, 30, 5, 3, SSD1306_WHITE);
            }
            break;

        case FaceState::NORMAL:
        default: {
            const int16_t height = (frame == 3) ? 3 : 15;
            display.fillRoundRect(25, 24, 30, height, 6, SSD1306_WHITE);
            display.fillRoundRect(73, 24, 30, height, 6, SSD1306_WHITE);
            break;
        }
    }
}

void UIRenderer::drawStatusBar()
{
    // Status bar will be reconnected after the renderer compiles.
}

void UIRenderer::drawEyesNormal(uint8_t) {}
void UIRenderer::drawEyesHappy() {}
void UIRenderer::drawEyesSad() {}
void UIRenderer::drawEyesAngry() {}
void UIRenderer::drawEyesSleepy() {}
void UIRenderer::drawEyesSurprised() {}
void UIRenderer::drawEyesExcited() {}
void UIRenderer::drawEyesConfused() {}
void UIRenderer::drawEyesLove() {}
void UIRenderer::drawEyesTired() {}
void UIRenderer::drawEyesCharging() {}
void UIRenderer::drawEyesLowBattery() {}
void UIRenderer::drawEyesError() {}
void UIRenderer::drawEyesOTA() {}
void UIRenderer::drawEyesAlarm() {}

void UIRenderer::drawSnake()
{
    display.setCursor(0, 0);
    display.print("SNAKE  S:");
    display.println(snakeGame.score());
    display.drawRect(0, 10, 128, 54, SSD1306_WHITE);

    constexpr uint8_t cellW = 8;
    constexpr uint8_t cellH = 6;

    for (uint8_t i = 0; i < snakeGame.bodyLength(); ++i) {
        const auto p = snakeGame.bodyAt(i);
        display.fillRect(1 + p.x * cellW, 11 + p.y * cellH,
                         cellW - 1, cellH - 1, SSD1306_WHITE);
    }

    const auto food = snakeGame.foodPosition();
    display.fillRect(1 + food.x * cellW, 11 + food.y * cellH,
                     cellW - 1, cellH - 1, SSD1306_WHITE);
}

void UIRenderer::drawReaction()
{
    display.setCursor(0, 0);
    display.println("REACTION");
    display.setCursor(0, 24);

    if (reactionGame.ready()) {
        display.setTextSize(2);
        display.println("GO!");
        display.setTextSize(1);
        display.setCursor(0, 50);
        display.print("Score: ");
        display.println(reactionGame.score());
    } else {
        display.println("Wait for GO...");
        display.println("Press B1 too early = fail");
    }
}

void UIRenderer::drawDodge()
{
    display.setCursor(0, 0);
    display.print("DODGE  S:");
    display.println(dodgeGame.score());
    display.drawRect(0, 10, 128, 54, SSD1306_WHITE);

    constexpr uint8_t cellW = 8;
    constexpr uint8_t cellH = 6;

    display.fillRect(1 + dodgeGame.playerX() * cellW, 57,
                     cellW - 1, 5, SSD1306_WHITE);

    display.fillRect(1 + dodgeGame.obstacleX() * cellW,
                     11 + dodgeGame.obstacleY() * cellH,
                     cellW - 1, cellH - 1, SSD1306_WHITE);
}

void UIRenderer::drawMemory()
{
    display.setCursor(0, 0);
    display.print("MEMORY  LV:");
    display.println(memoryGame.level());

    if (memoryGame.showingPrompt()) {
        const uint8_t prompt = memoryGame.currentPrompt();
        const int16_t x[] = {16, 72, 16, 72};
        const int16_t y[] = {18, 18, 42, 42};

        if (prompt < 4) {
            display.fillRoundRect(x[prompt], y[prompt], 40, 16, 4,
                                  SSD1306_WHITE);
        }
    } else {
        display.setCursor(20, 34);
        display.println("YOUR TURN");
        display.setCursor(0, 54);
        display.println("Use buttons 1-4");
    }
}
