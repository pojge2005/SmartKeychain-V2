#include "snake.h"

SnakeGame snakeGame;

void SnakeGame::begin() {
    reset();
}

void SnakeGame::reset() {
    length = 3;
    direction = 1;
    currentScore = 0;
    currentState = GameState::RUNNING;

    body[0] = {5, 4};
    body[1] = {4, 4};
    body[2] = {3, 4};

    food = {10, 4};
    lastMoveMs = millis();
}

void SnakeGame::update(uint32_t nowMs) {
    if (currentState != GameState::RUNNING) {
        return;
    }

    if (nowMs - lastMoveMs < 180) {
        return;
    }

    lastMoveMs = nowMs;
    move();
}

void SnakeGame::move() {
    Position head = body[0];

    switch (direction) {
        case 0:
            if (head.y == 0) {
                currentState = GameState::GAME_OVER;
                return;
            }
            head.y--;
            break;

        case 1:
            if (head.x >= WIDTH - 1) {
                currentState = GameState::GAME_OVER;
                return;
            }
            head.x++;
            break;

        case 2:
            if (head.y >= HEIGHT - 1) {
                currentState = GameState::GAME_OVER;
                return;
            }
            head.y++;
            break;

        case 3:
            if (head.x == 0) {
                currentState = GameState::GAME_OVER;
                return;
            }
            head.x--;
            break;
    }

    for (uint8_t i = length - 1; i > 0; i--) {
        body[i] = body[i - 1];
    }

    body[0] = head;

    if (head.x == food.x && head.y == food.y) {
        if (length < MAX_LENGTH) {
            body[length] = body[length - 1];
            length++;
        }

        currentScore++;
        spawnFood();
    }
}

void SnakeGame::spawnFood() {
    food.x = (currentScore * 5 + 3) % WIDTH;
    food.y = (currentScore * 3 + 2) % HEIGHT;
}

void SnakeGame::button1() {
    if (direction != 2) {
        direction = 0;
    }
}

void SnakeGame::button2() {
    if (direction != 3) {
        direction = 1;
    }
}

void SnakeGame::button3() {
    if (direction != 0) {
        direction = 2;
    }
}

void SnakeGame::button4() {
    if (direction != 1) {
        direction = 3;
    }
}

GameId SnakeGame::id() const {
    return GameId::SNAKE;
}

GameState SnakeGame::state() const {
    return currentState;
}

uint16_t SnakeGame::score() const {
    return currentScore;
}

uint8_t SnakeGame::bodyLength() const
{
    return length;
}

SnakeGame::Position SnakeGame::bodyAt(uint8_t index) const
{
    if (index >= length) {
        return {0, 0};
    }

    return body[index];
}

SnakeGame::Position SnakeGame::foodPosition() const
{
    return food;
}
