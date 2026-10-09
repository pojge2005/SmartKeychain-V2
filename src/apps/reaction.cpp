#include "reaction.h"

ReactionGame reactionGame;

void ReactionGame::begin()
{
    reset();
    currentState = GameState::RUNNING;
}

void ReactionGame::reset()
{
    currentState = GameState::RUNNING;
    currentScore = 0;
    signalIsActive = false;

    startMs = millis();
    triggerMs = startMs + 2000;
    reactionMs = 0;
}

void ReactionGame::update(uint32_t nowMs)
{
    if (currentState != GameState::RUNNING) {
        return;
    }

    if (!signalIsActive &&
        static_cast<int32_t>(nowMs - triggerMs) >= 0) {
        signalIsActive = true;
        triggerMs = nowMs;
    }
}

void ReactionGame::button1()
{
    if (currentState != GameState::RUNNING) {
        return;
    }

    const uint32_t now = millis();

    if (!signalIsActive) {
        currentScore = 0;
        currentState = GameState::GAME_OVER;
        return;
    }

    reactionMs = now - triggerMs;

    currentScore = reactionMs < 250 ? 100 :
                   reactionMs < 350 ? 80 :
                   reactionMs < 500 ? 60 :
                   reactionMs < 750 ? 40 : 20;

    currentState = GameState::COMPLETE;
}

void ReactionGame::button2() {}
void ReactionGame::button3() {}
void ReactionGame::button4() {}

GameId ReactionGame::id() const
{
    return GameId::REACTION;
}

GameState ReactionGame::state() const
{
    return currentState;
}

uint16_t ReactionGame::score() const
{
    return currentScore;
}

bool ReactionGame::signalActive() const
{
    return signalIsActive;
}

bool ReactionGame::ready() const
{
    return signalIsActive;
}

uint32_t ReactionGame::reactionTimeMs() const
{
    return reactionMs;
}
