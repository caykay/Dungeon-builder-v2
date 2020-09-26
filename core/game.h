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
    }
    // Game should not be cloneable
    Game(Game &other)=delete ;
    // Game should not be assignable
    void operator=(const Game &)= delete;

    static Game &instance();
    core::dungeon::DungeonLevelBuilder *builder;
    core::dungeon::DungeonLevel *level;

    void setDungeonType(char type);
    void setDungeonType(core::dungeon::DungeonLevelBuilder* builder);
    void createExampleLevel();
    void createRandomLevel(const std::string &name, int width, int height);

    void clearLevel();

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

    // returns a random number in the given range
    int getRandomInt(int min, int max);
    // choses a either int a or b at random and returns it
    int getRandomBtn(int a, int b);

    // specific constraint functions
    // Builds an entrance from a random room of the top rooms
    void buildRandomEntrance();
    // Builds an exit doorway from a random room in the bottom rows
    void buildRandomExit();

    // responsible for building corner room doorways for random level
    void buildCornerRooms();
    // following functions are subset of the above functions
    void buildTopLeftCornerRoom();
    void buildTopRightCornerRoom();
    void buildBottomLeftCornerRoom();
    void buildBottomRightCornerRoom();

    // responsible for building non-corner rooms
    void buildNonCornerRooms();
    // Build top&bottom room doorways
    void buildTopRooms();
    void buildBottomRooms();

    // Build left&right room doorways
    void buildLeftRooms();
    void buildRightRooms();

    // Build mid room doorways
    void buildMidRooms();

    // this function is similar to that of level, it does the same thing, but instead of
    // passing origin and destination rooms, it delegates level functions to do that
    // and building the general function itself
    void buildRoomDoorway(int id, Direction side);
    // returns a constraint set with random individual doorways constraints already set
    // (contraint returns is already a mix of the individual doorways)
    DLB::MoveConstraints getConstraint();



    // Do i need to instantiate it to nullptr?
    static std::unique_ptr<Game> _theInstance;
    std::mt19937 _randomGenerator{uint32_t(time(nullptr))}; //!< Mersenne Twister random number generator seeded by current time
    std::uniform_real_distribution<double> _realDistribution{0.0, 1.0}; //!< For random numbers between 0.0 & 1.0



};
}


#endif // GAME_H
