#ifndef GAME_H
#define GAME_H
#include <memory>
#include <random>
#include <ctime>
#include <iostream>
#include "core/dungeon/dungeonlevelbuilder.h"
#include "core/dungeon/dungeonlevel.h"
#include "core/items/consumeable.h"
#include "core/items/weapon.h"
#include "core/items/item.h"


namespace core {
/**
 * using definitions for simplification of having to write
 * full namespaces and class names
 */
using DLB=core::dungeon::DungeonLevelBuilder;
using Room=std::shared_ptr<core::dungeon::Room>;
using Direction=core::dungeon::Room::Direction;
using MoveConstraints=DLB::MoveConstraints;
using DL=core::dungeon::DungeonLevel;
using Item=core::items::Item;
using Consumable=core::items::Consumeable;
using Weapon = core::items::Weapon;

/**
 * @class Game
 * @brief The Game class
 * This class employs the singleton pattern, meaning there can only be
 * one of its instance at a time. It is responsible of monitoring and keeping track
 * of any Dungeon builders and levels. Its constructor is set to private, such that
 * no object of Game can be instantiated. Also any copy constructor of Game will be deleted
 * if ever made
 *
 * @author Cassian Kahema
 */
class Game
{
public:
    ~Game(){
        // Destroys dangling pointers owned by Game
        level=nullptr;
        builder=nullptr;
        delete level;
        delete builder;
    }
    /**
     * @brief Game Copy constructor that deletes the created object
     * This means an object of Game class cant be cloned
     * @param other Game object reference
     */
    Game(Game &other)=delete ;
    /**
     * @brief operator = Overrides equals operator "="
     * to delete the object whenever a copy is attempted.
     */
    void operator=(const Game &)= delete;
    /**
     * @brief instance Static method that returns a private instance of Game
     * through which other public methods can be access through
     * @return
     */
    static Game &instance();
    // Bare Pointers to Dungeon Level Builder and Dungeon level classes responsible for
    // construction of dungeon levels
    core::dungeon::DungeonLevelBuilder* builder;
    // Reference to the built level from Game
    core::dungeon::DungeonLevel* level;
    /**
     * @brief setDungeonType Sets the type Of dungeon to be built
     * either Basic or Magical. a character parameter is used to define
     * these types. Then it creates a new Dungeon builder object responsible
     * for building that dungeon
     * @param type character either 'b' for Basic Dungeon 'm' for magical
     */
    void setDungeonType(char type);
    /**
     * @brief setDungeonType By setting a dungeon type the "builder" object
     * reference is initialized to the type of dungeon passed in the parameter
     * i.e BasicDungeonLevelBuilder pointer reference will build a BasicDungeon Level
     * MagicDungeonLevelBuilder will do similar for magical level.
     * @param builder Type of dungeon builder responsible for building a dungeon
     */
    void setDungeonType(core::dungeon::DungeonLevelBuilder* builder);
    /**
     * @brief createExampleLevel Performs the creation of a sample Dungeon Level
     * which is a basic dungeon level
     */
    void createExampleLevel();
    /**
     * @brief createRandomLevel Creates a random level from a variety of set constraints
     * also sets name, and size as customized.
     * @param name Name of the dungeon
     * @param width Width/columns of the dungeon
     * @param height Height/Rows of the dungeon
     */
    void createRandomLevel(const std::string &name, int width, int height);
    /**
     * @brief clearLevel Clears current level in case a new one is to be
     * made after (also reduces risk of memory leakage)
     */
    void clearLevel();
    /**
     * @brief displayLevel Prints out the whole structure of the built dungone
     * to the output stream passed in as parameter.
     * @param display Output stream that displays output onto console
     */
    void displayLevel( std::ostream &display);
    /**
     * @brief describeLevel Gives a brief description of the current built level
     * @param display Output stream that displays output onto console
     */
    void describeLevel( std::ostream &display);
    /**
     * @brief describeRoom Gives brief description of a specific room in current dungeon
     * @param display Output stream that displays output onto console
     * @param id Identification number of a room
     */
    void describeRoom(std::ostream &display, int id);
    /**
     * @brief randomDouble Generates a random number within range of 0.0 and 1.0
     * @return a random double between 0.0 and 1.0
     */
    double randomDouble();
private:
    /**
     * @brief Game Private default constructor so that no one can instantiate
     */
    Game(){

    }
    /**
     * @brief _theInstance This is a static variable used by Game class
     * to specify its instance, its static so that everytime an instance
     * of game is called its called to the same instance. That way only
     * one instance can be on at a time. Also unique defining ownership
     * to only the Game class.
     */
    static std::unique_ptr<Game> _theInstance;
    /**
     * @brief createExampleRooms Responsible for creating rooms
     * to be placed in the Example Dungeon level
     */
    void createExampleRooms();
    /**
     * @brief buildExampleDoorways Responsible for constructions
     * for doorways in every specified room in the example level
     */
    void buildExampleDoorways();
    /**
     * @brief buildExampleItems Builds and add items to some rooms
     * in the Example Dungeon Level
     */
    void buildExampleItems();
    /**
     * @brief buildExampleCreatures Creat random abstract creatures
     * and assign them to some rooms in the ExampleDungeon Level
     */
    void buildExampleCreatures();
    /**
     * @brief addRandomRooms Adds rooms to a generated random Level
     * according to the specified size.
     * @param size
     */
    void addRandomRooms(int size);
    /**
     * @brief buildRandomDoorways Builds random doorways for each room
     * in a random Dungeon level.
     */
    void buildRandomDoorways(); 
    /**
     * @brief addRandomCreatures Function responsible to add monsters to random rooms
     * in the Random Dungeon Level.
     */
    void addRandomCreatures();
    /**
     * @brief addRandomItems Adds random items to random rooms in the Random Dungeon
     * Level
     */
    void addRandomItems();
    /**
     * @brief addMonster Enforces the constraint that the random selected monster has
     * a 25% chance to be put in a room
     * @param id Id of the room that the monster will be added to
     */
    void addMonster(int id);
    /**
     * @brief addItem Enforces the 35% that a room can have a random item
     * @param id Id of the room that the item will be added to
     */
    void addItem(int id);
    /**
     * @brief getRandomItemType Selets a concrete item type under specified
     * constraints: 35% it is a Consumable and 65% chance its a Weapon.
     * @return A shared pointer referencing to the random item selected
     */
    std::shared_ptr<Item> getRandomItemType();
    /**
     * @brief addItemOfType Adds the random item of given type generated
     * from getRandomItemType() then adds it to the room with id specified
     * @param id Id of the room that the item will be added to
     * @param type Randomly selected item of a randomly selected Type
     */
    void addItemOfType(int id,std::shared_ptr<Item> item);
    /**
     * @brief getRandomInt Selects a random number with the specified range
     * inclusive
     * @param min The minimum range of numbers to be generated
     * @param max The maximum number that can be selected
     * @return random selected number
     */
    int getRandomInt(int min, int max);
    /**
     * @brief getRandomBtn Returns either of the numbers passed in as
     * parameters. Based on the random selection done between the two.
     * @param num1 First number option
     * @param num2 Second number option
     * @return Either num1 or num2
     */
    int getRandomBtn(int num1, int num2);
    /**
     * @brief buildRandomEntrance Builds an entrance from a random room
     * among the rooms in the top row of the dungeon level.
     */
    void buildRandomEntrance();
    /**
     * @brief buildRandomExit Builds an exit doorway from a random room
     * in the bottom row
     */
    void buildRandomExit();
    /**
     * @brief buildCornerRooms Responsible for building all doorways of
     * the corner rooms in the generated Random Dungeon Level
     */
    void buildCornerRooms();
    /**
     * @brief buildTopLeftCornerRoom This function is a subset of the
     * buildCornerRooms, it is only responsible for building the doorways
     * of the top left corner room
     */
    void buildTopLeftCornerRoom();
    /**
     * @brief buildTopLeftCornerRoom This function is a subset of the
     * buildCornerRooms, it is only responsible for building the doorways
     * of the top right corner room
     */
    void buildTopRightCornerRoom();
    /**
     * @brief buildTopLeftCornerRoom This function is a subset of the
     * buildCornerRooms, it is only responsible for building the doorways
     * of the bottom left corner room
     */
    void buildBottomLeftCornerRoom();
    /**
     * @brief buildTopLeftCornerRoom This function is a subset of the
     * buildCornerRooms, it is only responsible for building the doorways
     * of the bottom right corner room
     */
    void buildBottomRightCornerRoom();
    /**
     * @brief buildNonCornerRooms Responsible for building random doorways
     * in non-corner rooms of the Random generated Dungeon level
     */
    void buildNonCornerRooms();
    /**
     * @brief buildTopRooms Subset function of buildNonCornerRoom
     * its responsible for building doorways on the top rooms that are not
     * corner rooms
     */
    void buildTopRooms();
    /**
     * @brief buildBottomRooms Almost similar to buildTopRooms this function,
     * instead builds random doorways on the Bottom non corner rooms
     */
    void buildBottomRooms();
    /**
     * @brief buildLeftRooms Subset of buildNonCornerRooms this function
     * builds random doors on the left rooms in a Random Dungeon Level
     * that aren't corner rooms
     */
    void buildLeftRooms();
    /**
     * @brief buildRightRooms Almost similar to buildLeftRooms, this
     * function instead builds doorways to the rooms at the far right
     */
    void buildRightRooms();
    /**
     * @brief buildMidRooms Build Doorways in the rooms around the
     * middle of the dungeon. These rooms are neither on corner, left or
     * far right sides of the Dungeon Level.
     */
    void buildMidRooms();

    /**
     * @brief buildRoomDoorway this function is similar to that of level,
     * it does the same thing, but instead of passing origin and
     * destination rooms, it delegates level functions to do that and
     * building the general function itself
     * @param id Id of the room
     * @param side Direction to which the doorway has to be made
     */
    void buildRoomDoorway(int id, Direction side);

    /**
     * @brief getConstraint Generates a constraint set with random
     * individual doorways constraints already set
     * @return A mix of the individual doorways joined by a bitwise OR("|")
     */
    DLB::MoveConstraints getConstraint();
    std::mt19937 _randomGenerator{uint32_t(time(nullptr))}; //!< Mersenne Twister random number generator seeded by current time
    std::uniform_real_distribution<double> _realDistribution{0.0, 1.0}; //!< For random numbers between 0.0 & 1.0



};//END Game
}//END core


#endif // GAME_H
