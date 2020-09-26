#ifndef BASICDUNGEONLEVELBUILDER_H
#define BASICDUNGEONLEVELBUILDER_H
#include "core/dungeon/dungeonlevelbuilder.h"
#include "basicdungeonlevel.h"
#include "core/dungeon/doorway.h"

namespace core {
namespace dungeon{
namespace basic{
using DBL=core::dungeon::DungeonLevelBuilder;
class BasicDungeonLevelBuilder : public DungeonLevelBuilder
{
public:
    BasicDungeonLevelBuilder();
    ~BasicDungeonLevelBuilder(){
        delete _level;
    }

    void buildDungeonLevel(const std::string &name, int width, int height)  override;
    std::shared_ptr<Room> buildRoom(int id)  override;
    void buildDoorway(std::shared_ptr<Room> origin, std::shared_ptr<Room>destination,
                              Room::Direction direction,MoveConstraints constraints) override;

    void buildEntrance(std::shared_ptr<Room> room, Room::Direction direction) override;

    void buildExit(std::shared_ptr<Room> room, Room::Direction direction) override;

    void buildItem (std::shared_ptr<Room> room) override;

    void buildCreature (std::shared_ptr<Room> room) override;

    DungeonLevel* getDungeonLevel() override;

private:
    BasicDungeonLevel* _level;
    core::dungeon::Room::Direction opposite(core::dungeon::Room::Direction direction);

    void createPrototypeItems() override;
    void createPrototypeCreatures()override;
    core::items::Item *createItem(Items item)  override;
    std::unique_ptr<core::creatures::AbstractCreature> createMonster(Monsters monster)  override;

    std::unique_ptr<core::items::Item> getRandomItem();
    std::shared_ptr<core::creatures::AbstractCreature> getRandomCreature();

    int getRandomInt(int min, int max);

    // Takes two door references as parameters and connects them at specified direction
    void connectDoors(std::shared_ptr<Room> origin, std::shared_ptr<Room>destination, Room::Direction direction);

    friend bool operator ==(DBL::MoveConstraints constraint1,DBL::MoveConstraints constraint2);
};
}
}
}
inline core::dungeon::DungeonLevelBuilder::MoveConstraints operator |(core::dungeon::DungeonLevelBuilder::MoveConstraints constraint1,core::dungeon::DungeonLevelBuilder::MoveConstraints constraint2) {
    return (static_cast<core::dungeon::DungeonLevelBuilder::MoveConstraints>(static_cast<unsigned int>(constraint1) | static_cast<unsigned int>(constraint2)));
}
inline core::dungeon::DungeonLevelBuilder::MoveConstraints operator &(core::dungeon::DungeonLevelBuilder::MoveConstraints constraint1,core::dungeon::DungeonLevelBuilder::MoveConstraints constraint2) {
    return (static_cast<core::dungeon::DungeonLevelBuilder::MoveConstraints>(static_cast<unsigned int>(constraint1) & static_cast<unsigned int>(constraint2)));
}

#endif // BASICDUNGEONLEVELBUILDER_H
