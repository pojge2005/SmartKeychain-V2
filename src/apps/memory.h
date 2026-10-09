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
EOF

cat > src/apps/games/memory.cpp <<'EOF'
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