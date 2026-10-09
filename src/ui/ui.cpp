#include "ui.h"
#include "ui_renderer.h"
#include "face_engine.h"
#include "../apps/games/game_center.h"

UIManager ui;

void UIManager::begin()
{
    current = Screen::HOME;
    menu = false;
    selectedMenu = 0;
    dirty = true;

    renderer.begin();
    renderer.render(current);
}

void UIManager::update()
{
    // FaceEngine::update() is handled by main.cpp.
    // Refresh active games at approximately 30 FPS.
    static uint32_t lastGameRenderMs = 0;
    const uint32_t now = millis();

    if (gameCenter.active()) {
        if (now - lastGameRenderMs >= 33) {
            renderer.render(Screen::GAMES);
            lastGameRenderMs = now;
        }
        return;
    }

    // Render screen changes immediately.
    if (dirty) {
        renderer.render(current);
        dirty = false;
        return;
    }

    // Refresh the home screen only when the face state or frame changes.
    if (current == Screen::HOME && face.animationActive()) {
        static FaceState lastFaceState = FaceState::ERROR;
        static uint8_t lastFaceFrame = 255;

        const FaceState state = face.state();
        const uint8_t frame = face.animationFrame();

        if (state != lastFaceState || frame != lastFaceFrame) {
            renderer.render(current);
            lastFaceState = state;
            lastFaceFrame = frame;
        }
    }
}

void UIManager::next()
{
    if (!menu) {
        openMenu();
    }

    selectedMenu++;

    if (selectedMenu >= MENU_ITEMS) {
        selectedMenu = 0;
    }

    dirty = true;
}

void UIManager::previous()
{
    if (!menu) {
        openMenu();
    }

    if (selectedMenu == 0) {
        selectedMenu = MENU_ITEMS - 1;
    } else {
        selectedMenu--;
    }

    dirty = true;
}

void UIManager::select()
{
    if (!menu) {
        openMenu();
        return;
    }

    current = menuScreen(selectedMenu);
    menu = false;
    dirty = true;
}

void UIManager::back()
{
    if (menu) {
        menu = false;
        current = Screen::HOME;
        dirty = true;
        return;
    }

    if (current != Screen::HOME) {
        current = Screen::HOME;
        dirty = true;
    }
}

void UIManager::open(Screen screen)
{
    current = screen;
    menu = false;
    dirty = true;
}

void UIManager::openMenu()
{
    menu = true;
    dirty = true;
}

Screen UIManager::currentScreen() const
{
    return current;
}

bool UIManager::menuOpen() const
{
    return menu;
}

uint8_t UIManager::menuIndex() const
{
    return selectedMenu;
}

Screen UIManager::menuScreen(uint8_t index) const
{
    switch (index) {
        case 0: return Screen::CLOCK;
        case 1: return Screen::GAMES;
        case 2: return Screen::KEYCHAIN;
        case 3: return Screen::BATTERY;
        case 4: return Screen::TIMER;
        case 5: return Screen::STOPWATCH;
        case 6: return Screen::ALARM;
        case 7: return Screen::SETTINGS;
        default: return Screen::HOME;
    }
}

void UIManager::render()
{
    renderer.render(menu ? Screen::GAMES : current);
}

void UIManager::renderHome()
{
    renderer.render(Screen::HOME);
}

void UIManager::renderMenu()
{
    renderer.render(Screen::GAMES);
}

void UIManager::renderScreen(Screen screen)
{
    renderer.render(screen);
}
