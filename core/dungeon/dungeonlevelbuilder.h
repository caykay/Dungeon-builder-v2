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

class DungeonLevelBuilder
{
protected:
    //TODO Remove these already implemented some in basic and (optional) magical dlb
    enum class Items {
        Boomerang, Short_Sword, Battle_Axe, Wizard_Staff,Magic_Wand,
        Health_Potion, Molotov_Cocktail, Smoke_Bomb, Resistance_Potion
    };
    enum class Monsters{
        Goblin, Werewolf, Evil_Wizard, Dragon
    };

    std::map<Monsters, std::unique_ptr<core::creatures::AbstractCreature>> prototypeCreatures;
    std::map<Items, std::unique_ptr<core::items::Item>> prototypeItems;

    virtual void createPrototypeItems();
    virtual void createPrototypeCreatures();
    virtual std::unique_ptr<core::items::Item> createItem(Items item) ;
    virtual std::unique_ptr<core::creatures::AbstractCreature> createMonster(Monsters monster);
public:
    DungeonLevelBuilder();
    virtual ~DungeonLevelBuilder(){}

    enum class MoveConstraints: unsigned{None, OriginImpassable=1,
                                        DestinationImpassable=2, OriginLocked=4,
                                        DestinationLocked=8};

    virtual void buildDungeonLevel(const std::string &name, int width, int height);
    virtual std::shared_ptr<Room> buildRoom(int id) ;
    virtual void buildDoorway(std::shared_ptr<Room> origin, std::shared_ptr<Room>destination,
                              Room::Direction direction, MoveConstraints constraints) ;

    virtual void buildEntrance(std::shared_ptr<Room> room, Room::Direction direction) ;

    virtual void buildExit(std::shared_ptr<Room> room, Room::Direction direction) ;

    virtual void buildItem (std::shared_ptr<Room> room) ;

    virtual void buildCreature (std::shared_ptr<Room> room) ;

    virtual DungeonLevel* getDungeonLevel() ;

    // sets a random individual constraint for a doorway
    virtual MoveConstraints getRandomOriginConstraint();
    virtual MoveConstraints getRandomDestConstraint();

    virtual std::shared_ptr<core::items::Item> getRandomItem();
    virtual std::shared_ptr<core::creatures::AbstractCreature> getRandomCreature();


};
}
}
#endif // DUNGEONLEVELBUILDER_H
