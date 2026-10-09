#pragma once

#include <Arduino.h>
#include "apps/games/game.h"

class HighScores {
public:
    bool begin();

    uint16_t get(GameId game) const;
    bool saveIfBest(GameId game, uint16_t score);

    void reset();

private:
    uint16_t snake = 0;
    uint16_t reaction = 0;
    uint16_t dodge = 0;
    uint16_t memory = 0;

    uint16_t& reference(GameId game);
    const uint16_t& reference(GameId game) const;
};

extern HighScores highScores;
