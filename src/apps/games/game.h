#pragma once

#include <Arduino.h>

enum class GameId {
    NONE,
    SNAKE,
    REACTION,
    DODGE,
    MEMORY
};

enum class GameState {
    IDLE,
    RUNNING,
    PAUSED,
    GAME_OVER,
    COMPLETE
};

class Game {
public:
    virtual ~Game() = default;

    virtual void begin() = 0;
    virtual void update(uint32_t nowMs) = 0;

    virtual void button1() = 0;
    virtual void button2() = 0;
    virtual void button3() = 0;
    virtual void button4() = 0;

    virtual GameId id() const = 0;
    virtual GameState state() const = 0;
    virtual uint16_t score() const = 0;

    virtual void reset() = 0;
};
