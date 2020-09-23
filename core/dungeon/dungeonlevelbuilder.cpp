#include "dungeonlevelbuilder.h"
using namespace core::dungeon;
DungeonLevelBuilder::DungeonLevelBuilder()
{

}

void DungeonLevelBuilder::buildDungeonLevel(const std::string &name, int width, int height)const {}
std::shared_ptr<Room> DungeonLevelBuilder::buildRoom(int id) const{}
void DungeonLevelBuilder::buildDoorway(std::shared_ptr<Room> origin, std::shared_ptr<Room>destination,
                                       Room::Direction direction, MoveConstraints constraints) const{}

void DungeonLevelBuilder::buildEntrance(std::shared_ptr<Room> room, Room::Direction direction) const{}

void DungeonLevelBuilder::buildExit(std::shared_ptr<Room> room, Room::Direction direction) const{}

void DungeonLevelBuilder::buildItem (std::shared_ptr<Room> room) const{}

void DungeonLevelBuilder::buildCreature (std::shared_ptr<Room> room) const{}

DungeonLevel* DungeonLevelBuilder::getDungeonLevel() const{}
