#pragma once

#include "game.h"

class ReactionGame : public Game {
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

    bool ready() const;
    bool signalIsActive() const;
    uint32_t reactionTimeMs() const;

private:
    GameState currentState = GameState::IDLE;

    uint32_t startMs = 0;
    uint32_t triggerMs = 0;
    uint32_t reactionMs = 0;

    uint16_t currentScore = 0;
    bool signalActive = false;
};

extern ReactionGame reactionGame;
