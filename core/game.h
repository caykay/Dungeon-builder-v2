#ifndef GAME_H
#define GAME_H
#include <memory>
#include <random>
#include <ctime>
#include <iostream>
#include "core/dungeon/dungeonlevelbuilder.h"
#include "core/dungeon/dungeonlevel.h"


namespace core {
// forward decleration (to look back at it)
using DLB=core::dungeon::DungeonLevelBuilder;
using Room=std::shared_ptr<core::dungeon::Room>;
using Direction=core::dungeon::Room::Direction;
using MoveConstraints=DLB::MoveConstraints;
using DL=core::dungeon::DungeonLevel;

class Game
{
public:
    ~Game(){
        // do we really need this
//        delete level;
//        delete builder;
//        level=nullptr;
//        builder=nullptr;
    }
    // Game should not be cloneable
    Game(Game &other)=delete ;
    // Game should not be assignable
    void operator=(const Game &)= delete;

    static Game &instance();
    static void releaseInstance();
    core::dungeon::DungeonLevelBuilder *builder;
    core::dungeon::DungeonLevel *level;

    void setDungeonType(char type);
    void setDungeonType(core::dungeon::DungeonLevelBuilder* builder);
    void createExampleLevel();
    void createRandomLevel(const std::string &name, int width, int height);

    void displayLevel( std::ostream &display);
    void describeLevel( std::ostream &display);
    void describeRoom(std::ostream &display, int id);

    double randomDouble();
private:
    Game(){}
    void createExampleRooms();
    void buildExampleDoorways();
    void buildExampleItems();
    void buildExampleCreatures();

    void buildRandomRooms(int size);
    void buildRandomDoorways();
    int getRandomId(std::vector<int> list);

    int getRandomInt(int min, int max);
    int getRandomBtn(int a, int b);

    // specific constraint functions
    void buildRandomEntrance(std::vector<int> FirstRowIDs);
    void buildRandomExit(std::vector<int> lastRowIDs);

    void buildCornerRooms();
    void buildNonCornerRooms();
    void buildTopRooms();
    void buildBottomRooms();
    void buildLeftRooms();
    void buildRightRooms();
    void buildMidRooms();
    // returns a constraint set with random individual doorways constraints
    // (contraint returns is already a mix of the individual doorways)
    DLB::MoveConstraints getRandConstraint();



    // Do i need to instantiate it to nullptr?
    static std::unique_ptr<Game> _theInstance;
    std::mt19937 _randomGenerator{uint32_t(time(nullptr))}; //!< Mersenne Twister random number generator seeded by current time
    std::uniform_real_distribution<double> _realDistribution{0.0, 1.0}; //!< For random numbers between 0.0 & 1.0



};
}


#endif // GAME_H
