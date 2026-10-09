#pragma once

#include "game.h"

class DodgeGame : public Game {
public:
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

    uint8_t playerX() const;
    uint8_t obstacleX() const;
    uint8_t obstacleY() const;

private:
    static constexpr uint8_t WIDTH = 16;
    static constexpr uint8_t HEIGHT = 8;

    uint8_t player = WIDTH / 2;
    uint8_t obstacle = 5;
    uint8_t obstacleYPos = 0;

    uint16_t currentScore = 0;

    GameState currentState = GameState::IDLE;

    uint32_t lastMoveMs = 0;
    uint32_t moveIntervalMs = 250;

    void spawnObstacle();
};

extern DodgeGame dodgeGame;
