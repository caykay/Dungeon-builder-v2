#ifndef BASICDUNGEONLEVELBUILDER_H
#define BASICDUNGEONLEVELBUILDER_H
#include "core/dungeon/dungeonlevelbuilder.h"
#include "basicdungeonlevel.h"
namespace core {
namespace dungeon{
namespace basic{

class BasicDungeonLevelBuilder : public DungeonLevelBuilder
{
public:
    BasicDungeonLevelBuilder();
    ~BasicDungeonLevelBuilder(){
        delete _level;
    }

    void buildDungeonLevel(const std::string &name, int width, int height) const override;
    std::shared_ptr<Room> buildRoom(int id) const override;
    void buildDoorway(std::shared_ptr<Room> origin, std::shared_ptr<Room>destination,
                              Room::Direction direction, MoveConstraints constraints) const override;

    void buildEntrance(std::shared_ptr<Room> room, Room::Direction direction) const override;

    void buildExit(std::shared_ptr<Room> room, Room::Direction direction) const override;

    void buildItem (std::shared_ptr<Room> room) const override;

    void buildCreature (std::shared_ptr<Room> room) const override;

private:
    BasicDungeonLevel* _level;

};
}
}
}

#endif // BASICDUNGEONLEVELBUILDER_H
