#pragma once

#include "screen_model.h"

class HomeScreen {
public:
    void begin();
    void update();

    void setData(const HomeScreenData& data);

    const HomeScreenData& data() const;

private:
    HomeScreenData screenData;
};

extern HomeScreen homeScreen;
