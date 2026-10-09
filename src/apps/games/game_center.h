#pragma once

#include "game.h"

class GameCenter {
public:
    void begin();
    void update();

    void select(GameId game);
    void exit();

    void button1();
    void button2();
    void button3();
    void button4();

    GameId currentGame() const;
    bool active() const;

private:
    Game* current = nullptr;
    GameId selected = GameId::NONE;

    bool running = false;
    bool scoreRecorded = false;

    void recordScore();
};

extern GameCenter gameCenter;
