#include "home.h"

HomeScreen homeScreen;

void HomeScreen::begin() {
    screenData = HomeScreenData();
}

void HomeScreen::update() {
    // Home-screen state processing.
}

void HomeScreen::setData(const HomeScreenData& data) {
    screenData = data;
}

const HomeScreenData& HomeScreen::data() const {
    return screenData;
}
