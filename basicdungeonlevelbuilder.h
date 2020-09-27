#ifndef BASICDUNGEONLEVELBUILDER_H
#define BASICDUNGEONLEVELBUILDER_H
#include "dungeonlevelbuilder.h"
#include "basicdungeonlevel.h"
#include "doorway.h"

namespace core {
namespace dungeon{
namespace basic{
using DBL=core::dungeon::DungeonLevelBuilder;

/**
 * @class BasicDungeonLevelBuilder
 * @brief The BasicDungeonLevelBuilder class A concrete builder
 * that inherits the DungeonLevelBuilder. Responsible for specifically
 * building a basic dungeon level. Acts as concrete Builder. It implements
 * all the virtual functions declared in the Builder class
 */
class BasicDungeonLevelBuilder : public DungeonLevelBuilder
{
public:
    /**
     * @brief BasicDungeonLevelBuilder Default constructor
     */
    BasicDungeonLevelBuilder();
    /**
    * @brief ~BasicDungeonLevelBuilder Destructor that does cleanup
    * of the bare pointer level used to construct a basic dungeon level
    * product
    */
    ~BasicDungeonLevelBuilder(){
        _level=nullptr;
        delete _level;
    }
    // OVERRIDEN FUNCTIONS FROM DUNGEONLEVELBUILDER
    void buildDungeonLevel(const std::string &name, int width, int height)  override;
    std::shared_ptr<Room> buildRoom(int id)  override;
    void buildDoorway(std::shared_ptr<Room> origin, std::shared_ptr<Room>destination,
                              Room::Direction direction,MoveConstraints constraints) override;

    void buildEntrance(std::shared_ptr<Room> room, Room::Direction direction) override;

    void buildExit(std::shared_ptr<Room> room, Room::Direction direction) override;

    void buildItem (std::shared_ptr<Room> room) override;

    void buildCreature (std::shared_ptr<Room> room) override;

    DungeonLevel* getDungeonLevel() override;
    std::shared_ptr<core::items::Item> getRandomItem() override;
    std::shared_ptr<core::creatures::AbstractCreature> getRandomCreature() override;

private:
    /**
     * @brief _level Bare pointer reference to the product basic dungeon
     * leve produced in this class
     */
    BasicDungeonLevel* _level;
    /**
     * @brief opposite Gives the opposite direction of a passed in direction
     * for instance, it will return South if the direction parameter
     * is North
     * @param direction Direction to which we want to know its opposite
     * @return Opposite of direction parameter
     */
    core::dungeon::Room::Direction opposite(core::dungeon::Room::Direction direction);

    void createPrototypeItems() override;
    void createPrototypeCreatures()override;
    std::unique_ptr<core::items::Item> createItem(Items item)  override;
    std::unique_ptr<core::creatures::AbstractCreature> createMonster(Monsters monster)  override;


    /**
     * @brief getRandomInt This functions uses a Game instance to call
     * RandomDouble function that returns a random number within a certain range
     * @param min Lowest number that can be picked (inclusive)
     * @param max Largest number that can be picked (inclusive)
     * @return random integer between min and max
     */
    int getRandomInt(int min, int max);
    /**
     * @brief connectDoors Takes two room shared_ptr references as parameters
     * and connects them at specified direction
     * @param origin Room at origin
     * @param destination Room at destination
     * @param direction Direction of connection between origin and destination
     */
    void connectDoors(std::shared_ptr<Room> origin, std::shared_ptr<Room>destination, Room::Direction direction);
    // sets a random individual constraint for a doorway
    DungeonLevelBuilder::MoveConstraints getRandomOriginConstraint() override;
    DungeonLevelBuilder::MoveConstraints getRandomDestConstraint() override;
    /**
     * @brief operator == Overrides the boolean comparison operator to be
     * able to compare two constraints
     * @param constraint1 One of the constraint to be compared
     * @param constraint2 The other constraint to be compared
     * @return true if equal and false otherwise
     */
    friend bool operator ==(DBL::MoveConstraints constraint1,DBL::MoveConstraints constraint2);
};//END BasicDungeonLevelBuilder
}//END basic
}//END dungeons
}//END core

// OUT OF CLASS AND SCOPES DECLARATIONS AND DEFINITIONS ( To avoid them not being found within scopes)
/**
 * @brief operator | Overrides the bitwise OR operator to be able to perform
 * bitwise operation on two MoveConstraints enums
 * @param constraint1 One of the constraints
 * @param constraint2 The other constraint
 * @return A result of the bitwise OR between constraint1 and constraint2
 */
inline core::dungeon::DungeonLevelBuilder::MoveConstraints operator |(core::dungeon::DungeonLevelBuilder::MoveConstraints constraint1,
                                                                      core::dungeon::DungeonLevelBuilder::MoveConstraints constraint2) {
    return (static_cast<core::dungeon::DungeonLevelBuilder::MoveConstraints>(static_cast<unsigned int>(constraint1)
                                                                             | static_cast<unsigned int>(constraint2)));
}
/**
 * @brief operator & Overrides the bitwise AND operator to be able to perform
 * bitwise operation on two MoveConstraints enums
 * @param constraint1 One of the constraints
 * @param constraint2 The other constraint
 * @return A result of the bitwise AND between constraint1 and constraint2
 */
inline core::dungeon::DungeonLevelBuilder::MoveConstraints operator &(core::dungeon::DungeonLevelBuilder::MoveConstraints constraint1,
                                                                      core::dungeon::DungeonLevelBuilder::MoveConstraints constraint2) {
    return (static_cast<core::dungeon::DungeonLevelBuilder::MoveConstraints>(static_cast<unsigned int>(constraint1)
                                                                             & static_cast<unsigned int>(constraint2)));
}

#endif // BASICDUNGEONLEVELBUILDER_H
