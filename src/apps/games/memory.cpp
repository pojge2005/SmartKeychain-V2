#include "memory.h"
#include <Arduino.h>

MemoryGame memoryGame;

void MemoryGame::begin()
{
    randomSeed(micros());
    reset();

    sequence[0] = random(0, 4);

    currentState = GameState::RUNNING;
    displayPrompt = true;
    promptIndex = 0;
    promptStartMs = millis();
}

void MemoryGame::reset()
{
    sequenceLength = 1;
    inputPosition = 0;
    promptIndex = 0;

    displayPrompt = true;
    promptStartMs = 0;

    currentScore = 0;

    currentState = GameState::IDLE;
}

void MemoryGame::update(uint32_t nowMs)
{
    if (currentState != GameState::RUNNING) {
        return;
    }

    if (displayPrompt &&
        nowMs - promptStartMs >= promptIntervalMs) {

        displayPrompt = false;
        inputPosition = 0;
    }
}

void MemoryGame::generateNext()
{
    if (sequenceLength >= MAX_SEQUENCE) {
        currentState = GameState::COMPLETE;
        return;
    }

    sequence[sequenceLength] = random(0, 4);
    sequenceLength++;

    inputPosition = 0;
    promptIndex = 0;
    displayPrompt = true;
    promptStartMs = millis();
}

void MemoryGame::handleInput(uint8_t button)
{
    if (currentState != GameState::RUNNING || displayPrompt) {
        return;
    }

    if (button != sequence[inputPosition]) {
        currentState = GameState::GAME_OVER;
        return;
    }

    inputPosition++;

    if (inputPosition >= sequenceLength) {
        currentScore = sequenceLength;

        if (sequenceLength >= MAX_SEQUENCE) {
            currentState = GameState::COMPLETE;
            return;
        }

        generateNext();
    }
}

void MemoryGame::button1()
{
    handleInput(0);
}

void MemoryGame::button2()
{
    handleInput(1);
}

void MemoryGame::button3()
{
    handleInput(2);
}

void MemoryGame::button4()
{
    handleInput(3);
}

GameId MemoryGame::id() const
{
    return GameId::MEMORY;
}

GameState MemoryGame::state() const
{
    return currentState;
}

uint16_t MemoryGame::score() const
{
    return currentScore;
}

uint8_t MemoryGame::currentPrompt() const
{
    if (sequenceLength == 0) {
        return 0;
    }

    return sequence[promptIndex];
}

bool MemoryGame::showingPrompt() const
{
    return displayPrompt;
}

uint8_t MemoryGame::level() const
{
    return sequenceLength;
}
