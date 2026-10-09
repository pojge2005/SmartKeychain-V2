#pragma once

#include <Arduino.h>

enum class Screen {
    HOME,
    CLOCK,
    BATTERY,
    KEYCHAIN,
    GAMES,
    TIMER,
    STOPWATCH,
    ALARM,
    SETTINGS,
    DIAGNOSTICS,
    ABOUT
};

class UIManager {
public:
    void begin();
    void update();

    void next();
    void previous();
    void select();
    void back();

    void open(Screen screen);
    void openMenu();

    Screen currentScreen() const;
    bool menuOpen() const;

    uint8_t menuIndex() const;

private:
    Screen current = Screen::HOME;

    bool menu = false;
    bool dirty = true;

    uint8_t selectedMenu = 0;

    static constexpr uint8_t MENU_ITEMS = 8;

    Screen menuScreen(uint8_t index) const;

    void render();
    void renderHome();
    void renderMenu();
    void renderScreen(Screen screen);
};

extern UIManager ui;
