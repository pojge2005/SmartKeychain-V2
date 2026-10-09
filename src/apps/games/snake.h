#pragma once

#include "game.h"

class SnakeGame : public Game {
public:
    struct Position {
        uint8_t x;
        uint8_t y;
    };

    void begin() override;
    void update(uint32_t nowMs) override;

    void button1() override;
    void button2() override;
    void button3() override;
    void button4() override;

    GameId id() const override;
    GameState state() const override;
    uint16_t score() const override;
    void reset() override;

    uint8_t bodyLength() const;
    Position bodyAt(uint8_t index) const;
    Position foodPosition() const;

private:
    static constexpr uint8_t WIDTH = 16;
    static constexpr uint8_t HEIGHT = 8;
    static constexpr uint8_t MAX_LENGTH = 32;

    Position body[MAX_LENGTH]{};
    uint8_t length = 3;

    Position food{10, 4};
    uint8_t direction = 1;

    GameState currentState = GameState::IDLE;
    uint16_t currentScore = 0;
    uint32_t lastMoveMs = 0;

    static constexpr uint32_t MOVE_INTERVAL_MS = 180;

    void move();
    void spawnFood();
};

extern SnakeGame snakeGame;
