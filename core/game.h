#ifndef GAME_H
#define GAME_H
#include <memory>
#include <random>
#include <ctime>
#include <iostream>
#include "core/dungeon/dungeonlevelbuilder.h"
#include "core/dungeon/dungeonlevel.h"

namespace core {
class Game
{
public:

    static std::unique_ptr<Game> instance();
    std::shared_ptr<core::dungeon::DungeonLevelBuilder> builder;
    core::dungeon::DungeonLevel *level;

    void setDungeonType(std::shared_ptr<core::dungeon::DungeonLevelBuilder> builder);
    void createExampleLevel();
    void createRandomLevel(const std::string &name, int width, int height);
    void displayLevel(const std::ostream &display);
    double randomDouble();
private:
    Game();
    static std::unique_ptr<Game> _theInstance;
    std::mt19937 _randomGenerator{uint32_t(time(nullptr))}; //!< Mersenne Twister random number generator seeded by current time
    std::uniform_real_distribution<double> _realDistribution{0.0, 1.0}; //!< For random numbers between 0.0 & 1.0
};
}


#endif // GAME_H
