#ifndef MAGICALDUNGEONLEVELBUILDER_H
#define MAGICALDUNGEONLEVELBUILDER_H
#include "core/dungeon/dungeonlevelbuilder.h"
#include "magicaldungeonlevel.h"
namespace core {
namespace dungeon {
namespace magical {
class MagicalDungeonLevelBuilder: public DungeonLevelBuilder
{
public:
    MagicalDungeonLevelBuilder();
    ~MagicalDungeonLevelBuilder(){
    }

    void buildDungeonLevel(const std::string &name, int width, int height)  override;
    std::shared_ptr<Room> buildRoom(int id)  override;
    void buildDoorway(std::shared_ptr<Room> origin, std::shared_ptr<Room>destination,
                              Room::Direction direction,MoveConstraints constraints) override;

    void buildEntrance(std::shared_ptr<Room> room, Room::Direction direction) override;

    void buildExit(std::shared_ptr<Room> room, Room::Direction direction) override;

    void buildItem (std::shared_ptr<Room> room) override;

    void buildCreature (std::shared_ptr<Room> room) override;
private:
    MagicalDungeonLevel* _level;
};

}
}
}
#endif // MAGICALDUNGEONLEVELBUILDER_H
