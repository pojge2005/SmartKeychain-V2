#include "game_center.h"

#include "snake.h"
#include "reaction.h"
#include "dodge.h"
#include "memory.h"

#include "storage/high_scores.h"

GameCenter gameCenter;

void GameCenter::begin()
{
    current = nullptr;
    selected = GameId::NONE;
    running = false;
    scoreRecorded = false;
}

void GameCenter::select(GameId game)
{
    exit();

    selected = game;
    scoreRecorded = false;

    switch (game) {
        case GameId::SNAKE:
            current = &snakeGame;
            break;

        case GameId::REACTION:
            current = &reactionGame;
            break;

        case GameId::DODGE:
            current = &dodgeGame;
            break;

        case GameId::MEMORY:
            current = &memoryGame;
            break;

        default:
            current = nullptr;
            return;
    }

    current->begin();
    running = true;
}

void GameCenter::exit()
{
    running = false;
    current = nullptr;
    selected = GameId::NONE;
    scoreRecorded = false;
}

void GameCenter::update()
{
    if (!running || current == nullptr) {
        return;
    }

    current->update(millis());

    if (!scoreRecorded &&
        (current->state() == GameState::GAME_OVER ||
         current->state() == GameState::COMPLETE)) {

        recordScore();
    }
}

void GameCenter::recordScore()
{
    if (current == nullptr || scoreRecorded) {
        return;
    }

    highScores.saveIfBest(
        current->id(),
        current->score()
    );

    scoreRecorded = true;
}

void GameCenter::button1()
{
    if (current != nullptr) {
        current->button1();
    }
}

void GameCenter::button2()
{
    if (current != nullptr) {
        current->button2();
    }
}

void GameCenter::button3()
{
    if (current != nullptr) {
        current->button3();
    }
}

void GameCenter::button4()
{
    if (current != nullptr) {
        current->button4();
    }
}

GameId GameCenter::currentGame() const
{
    return selected;
}

bool GameCenter::active() const
{
    return running;
}
