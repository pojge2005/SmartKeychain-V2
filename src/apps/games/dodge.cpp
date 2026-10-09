#include "dodge.h"
#include <Arduino.h>

DodgeGame dodgeGame;

void DodgeGame::begin()
{
    randomSeed(micros());
    reset();
    currentState = GameState::RUNNING;
    lastMoveMs = millis();
}

void DodgeGame::reset()
{
    player = WIDTH / 2;
    obstacle = random(0, WIDTH);
    obstacleYPos = 0;
    currentScore = 0;
    moveIntervalMs = 250;
    lastMoveMs = millis();
    currentState = GameState::IDLE;
}

void DodgeGame::update(uint32_t nowMs)
{
    if (currentState != GameState::RUNNING) {
        return;
    }

    if (nowMs - lastMoveMs < moveIntervalMs) {
        return;
    }

    lastMoveMs = nowMs;

    obstacleYPos++;

    if (obstacleYPos >= HEIGHT - 1) {
        if (obstacle == player) {
            currentState = GameState::GAME_OVER;
            return;
        }

        currentScore++;

        if (moveIntervalMs > 100) {
            moveIntervalMs -= 5;
        }

        spawnObstacle();
    }
}

void DodgeGame::spawnObstacle()
{
    obstacle = random(0, WIDTH);
    obstacleYPos = 0;
}

void DodgeGame::button1()
{
    if (currentState != GameState::RUNNING) {
        return;
    }

    if (player > 0) {
        player--;
    }
}

void DodgeGame::button2()
{
    if (currentState != GameState::RUNNING) {
        return;
    }

    if (player < WIDTH - 1) {
        player++;
    }
}

void DodgeGame::button3()
{
    if (currentState == GameState::GAME_OVER ||
        currentState == GameState::COMPLETE) {
        begin();
    }
}

void DodgeGame::button4()
{
}

GameId DodgeGame::id() const
{
    return GameId::DODGE;
}

GameState DodgeGame::state() const
{
    return currentState;
}

uint16_t DodgeGame::score() const
{
    return currentScore;
}

uint8_t DodgeGame::playerX() const
{
    return player;
}

uint8_t DodgeGame::obstacleX() const
{
    return obstacle;
}

uint8_t DodgeGame::obstacleY() const
{
    return obstacleYPos;
}
