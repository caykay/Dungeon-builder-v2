#ifndef GAME_H
#define GAME_H
#include <memory>
#include <random>
#include <ctime>
#include <iostream>
#include "core/dungeon/dungeonlevelbuilder.h"

namespace core {
class Game
{
public:

    static Game* instance();
    DungeonLevelBuilder *dlb;
    void setDungeonType(DungeonLevelBuilder *dlb);
    void createExampleLevel();
    void createRandomLevel(std::string name, int width, int height);
    void displayLevel(const std::ostream &display);
    double randomDouble();
private:
    Game();
    static Game* _theInstance;
    std::mt19937 _randomGenerator{uint32_t(time(nullptr))}; //!< Mersenne Twister random number generator seeded by current time
    std::uniform_real_distribution<double> _realDistribution{0.0, 1.0}; //!< For random numbers between 0.0 & 1.0
};
}


#endif // GAME_H
