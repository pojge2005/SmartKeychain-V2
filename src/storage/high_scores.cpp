#include "high_scores.h"
#include <Preferences.h>

static Preferences scorePreferences;

HighScores highScores;

uint16_t& HighScores::reference(GameId game)
{
    switch (game) {
        case GameId::SNAKE:
            return snake;

        case GameId::REACTION:
            return reaction;

        case GameId::DODGE:
            return dodge;

        case GameId::MEMORY:
            return memory;

        default:
            return snake;
    }
}

const uint16_t& HighScores::reference(GameId game) const
{
    switch (game) {
        case GameId::SNAKE:
            return snake;

        case GameId::REACTION:
            return reaction;

        case GameId::DODGE:
            return dodge;

        case GameId::MEMORY:
            return memory;

        default:
            return snake;
    }
}

bool HighScores::begin()
{
    if (!scorePreferences.begin("scores", false)) {
        return false;
    }

    snake = scorePreferences.getUShort("snake", 0);
    reaction = scorePreferences.getUShort("reaction", 0);
    dodge = scorePreferences.getUShort("dodge", 0);
    memory = scorePreferences.getUShort("memory", 0);

    return true;
}

uint16_t HighScores::get(GameId game) const
{
    return reference(game);
}

bool HighScores::saveIfBest(GameId game, uint16_t score)
{
    if (game == GameId::NONE) {
        return false;
    }

    uint16_t& best = reference(game);

    if (score <= best) {
        return false;
    }

    best = score;

    switch (game) {
        case GameId::SNAKE:
            scorePreferences.putUShort("snake", best);
            break;

        case GameId::REACTION:
            scorePreferences.putUShort("reaction", best);
            break;

        case GameId::DODGE:
            scorePreferences.putUShort("dodge", best);
            break;

        case GameId::MEMORY:
            scorePreferences.putUShort("memory", best);
            break;

        default:
            break;
    }

    return true;
}

void HighScores::reset()
{
    snake = 0;
    reaction = 0;
    dodge = 0;
    memory = 0;

    scorePreferences.clear();
}
