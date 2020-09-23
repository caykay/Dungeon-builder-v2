#ifndef DUNGEONLEVELBUILDER_H
#define DUNGEONLEVELBUILDER_H
#include <memory>
#include <map>
#include "core/dungeon/room.h"
#include "dungeonlevel.h"
#include "core/items/item.h"
namespace core {
namespace dungeon {

class DungeonLevelBuilder
{
protected:
    enum class Items {
        Boomerang, Short_Sword, Battle_Axe, Wizard_Staff,Magic_Wand,
        Health_Potion, Molotov_Cocktail, Smoke_Bomb, Resistance_Potion
    };
    enum class Monsters{
        Goblin, Werewolf, Evil_Wizard, Dragon
    };

    std::map<Items, std::unique_ptr<core::items::Item>> prototypeItems;
public:
    DungeonLevelBuilder();
    virtual ~DungeonLevelBuilder(){}

    enum class MoveConstraints: unsigned{None=0, OriginImpassable=1,
                                        DestinationImpassable=2, OriginLoced=4,
                                        DestinationLocked=8};

    virtual void buildDungeonLevel(const std::string &name, int width, int height)const;
    virtual std::shared_ptr<Room> buildRoom(int id) const;
    virtual void buildDoorway(std::shared_ptr<Room> origin, std::shared_ptr<Room>destination,
                              Room::Direction direction, MoveConstraints constraints) const;

    virtual void buildEntrance(std::shared_ptr<Room> room, Room::Direction direction) const;

    virtual void buildExit(std::shared_ptr<Room> room, Room::Direction direction) const;

    virtual void buildItem (std::shared_ptr<Room> room) const;

    virtual void buildCreature (std::shared_ptr<Room> room) const;

    DungeonLevel* getDungeonLevel() const;
};
}
}
#endif // DUNGEONLEVELBUILDER_H
