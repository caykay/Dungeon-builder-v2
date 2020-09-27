#ifndef DUNGEONLEVELBUILDER_H
#define DUNGEONLEVELBUILDER_H
#include <memory>
#include <map>
#include "core/dungeon/room.h"
#include "core/dungeon/dungeonlevel.h"
#include "core/items/item.h"
#include "core/creatures/abstractcreature.h"
#include "core/items/weapon.h"
#include "core/items/consumeable.h"
#include "core/creatures/monster.h"
namespace core {
namespace dungeon {
/**
 * @class DungeonLevelBuilder
 * @brief The DungeonLevelBuilder class. This class is responsible
 * for the delegation of building a dungeon level to a specific
 * concrete builder either basic or magical. It does this through
 * employment of the Builder Design Pattern
 *
 * @author Cassian Kahema
 */
class DungeonLevelBuilder
{
protected:
    /**
     * @brief The Items enum. Contains List of all possible
     * Items that may exist in a dungeon (magical and basic)
     */
    enum class Items {
        Boomerang, Short_Sword, Battle_Axe, Wizard_Staff,Magic_Wand,
        Health_Potion, Molotov_Cocktail, Smoke_Bomb, Resistance_Potion
    };
    /**
     * @brief The Monsters enum. Contains an enumerated list of Creatures
     * specifically monsters that may exist in a dungeon room
     */
    enum class Monsters{
        Goblin, Werewolf, Evil_Wizard, Dragon
    };
    /**
     * @brief prototypeCreatures. Group of prototype creatures
     * mapped to their specific occurence/names will be stored
     * in this variable
     */
    std::map<Monsters, std::unique_ptr<core::creatures::AbstractCreature>> prototypeCreatures;
    /**
     * @brief prototypeItems. Stores references to Prototype Items.
     */
    std::map<Items, std::unique_ptr<core::items::Item>> prototypeItems;
    /**
     * @brief createPrototypeItems. Maps various items specific to
     * a type of dungeon to their types.
     */
    virtual void createPrototypeItems();
    /**
     * @brief createPrototypeCreatures. Maps various creatures specific to
     * a type of dungeon to their types.
     */
    virtual void createPrototypeCreatures();
    /**
     * @brief createItem. Creates a clone of an item before its
     * added to a room in a dungeon
     * @param item Item enum that represents the item type
     * @return  Cloned item
     */
    virtual std::unique_ptr<core::items::Item> createItem(Items item) ;
    /**
     * @brief createMonster. Creates a clone of a monster before its
     * added to a room in a dungeon
     * @param monster Creature enum that represents the creature type
     * @return  Cloned monster
     */
    virtual std::unique_ptr<core::creatures::AbstractCreature> createMonster(Monsters monster);
public:
    /**
     * @brief DungeonLevelBuilder Default constructor
     */
    DungeonLevelBuilder();
    /**
     * @brief ~DungeonLevelBuilder Virtual Destructor
     */
    virtual ~DungeonLevelBuilder(){}
    /**
     * @brief The MoveConstraints enum. Used to specify the implementation
     * of a doorway type. Whether it can be traversed through, a oneway only,
     * or Locked
     */
    enum class MoveConstraints: unsigned{None, OriginImpassable=1,
                                        DestinationImpassable=2, OriginLocked=4,
                                        DestinationLocked=8};
    /**
     * @brief buildDungeonLevel Creates a new Dungeon Level (product) with
     * a name, and specified size
     * @param name Name of the dungeon level
     * @param width Number of columns in dungeon level
     * @param height Number of rows in dungeon level
     */
    virtual void buildDungeonLevel(const std::string &name, int width, int height);
    /**
     * @brief buildRoom Uses the given id parameter to create a room
     * with that id number as an identification of it.
     * @param id Unique identifier of a room
     * @return A shared_ptr reference of a room
     */
    virtual std::shared_ptr<Room> buildRoom(int id) ;
    /**
     * @brief buildDoorway Builds a passage between two rooms under specified constraints
     * at a certain direction of the source/origin room which is the opposite direction
     * of the destination room. The constraint parameter is bitmask to identify bits
     * that represents individual constraint for a doorway type.
     * @param origin Source room or the room at current location
     * @param destination Room opposite to the current room. The intended destination
     * @param direction Direction to which the connection is to be made in origin
     * @param constraints Specifies the condition to which the rooms should be built
     */
    virtual void buildDoorway(std::shared_ptr<Room> origin, std::shared_ptr<Room>destination,
                              Room::Direction direction, MoveConstraints constraints) ;
    /**
     * @brief buildEntrance Builds an entrance doorway at the specified room
     * on the specified direction
     * @param room Room to which an entrance is to be set
     * @param direction Direction of the entrance
     */
    virtual void buildEntrance(std::shared_ptr<Room> room, Room::Direction direction) ;
    /**
     * @brief buildExit Builds an exit doorway at the specified room
     * on the specified direction
     * @param room Room to which an exit is to be set
     * @param direction Direction of the exit
     */
    virtual void buildExit(std::shared_ptr<Room> room, Room::Direction direction) ;
    /**
     * @brief buildItem Builds an item (which was selected at random)
     * by cloning it then adding it to the specified room
     * @param room Room to which the item is added
     */
    virtual void buildItem (std::shared_ptr<Room> room) ;
    /**
     * @brief buildCreature Builds a creature (which was selected at random)
     * by cloning it then adding it to the specified room
     * @param room Room to which the creature is added
     */
    virtual void buildCreature (std::shared_ptr<Room> room) ;
    /**
     * @brief getDungeonLevel Gets the current dungeon level product
     * constructed by the dungeon level builder
     * @return Reference to the Dungeon level created
     */
    virtual DungeonLevel* getDungeonLevel() ;
    /**
     * @brief getRandomOriginConstraint Sets a random individual constraint for the
     * origin doorway
     * at random.
     * 40% chance to set it as an open doorway
     * 30% chance to set it as a oneway/impassable doorway
     * 30% chance to set it as locked doorway
     * @return Original doorway constraint
     */
    virtual MoveConstraints getRandomOriginConstraint();
    /**
     * @brief getRandomDestConstraint Sets a random individual constraint for
     * the destination doorway
     * 40% chance to set it as an open doorway
     * 30% chance to set it as a oneway/impassable doorway
     * 30% chance to set it as locked doorway

     * @return Destination Doorway constraint
     */
    virtual MoveConstraints getRandomDestConstraint();
    /**
     * @brief getRandomItem Selects one random item from a list of prototypeItems
     * and returns a shared_ptr reference of it
     * @return a shared_ptr reference of it to randomly selected item
     */
    virtual std::shared_ptr<core::items::Item> getRandomItem();
    /**
     * @brief getRandomCreature Selects one random creature from a list of
     * prototypeCreatures.
     * @return Shared_ptr reference to the random selected creature
     */
    virtual std::shared_ptr<core::creatures::AbstractCreature> getRandomCreature();


};
}
}
#endif // DUNGEONLEVELBUILDER_H
