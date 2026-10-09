#pragma once

#include "game.h"

class MemoryGame : public Game {
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

    uint8_t currentPrompt() const;
    bool showingPrompt() const;
    uint8_t level() const;

private:
    static constexpr uint8_t MAX_SEQUENCE = 32;

    uint8_t sequence[MAX_SEQUENCE]{};
    uint8_t sequenceLength = 1;
    uint8_t inputPosition = 0;

    uint8_t promptIndex = 0;
    bool displayPrompt = true;

    uint32_t promptStartMs = 0;
    uint32_t promptIntervalMs = 600;

    uint16_t currentScore = 0;

    GameState currentState = GameState::IDLE;

    void generateNext();
    void handleInput(uint8_t button);
};

extern MemoryGame memoryGame;
