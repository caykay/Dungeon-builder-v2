#include "magicaldungeonlevelbuilder.h"
using namespace core::dungeon::magical;
using RoomPtr=std::shared_ptr<core::dungeon::Room>;

MagicalDungeonLevelBuilder::MagicalDungeonLevelBuilder()
{

}

void MagicalDungeonLevelBuilder::buildDungeonLevel(const std::string &name, int width, int height) {

}
RoomPtr MagicalDungeonLevelBuilder::buildRoom(int id)  {

}

void MagicalDungeonLevelBuilder::buildDoorway(RoomPtr origin, RoomPtr destination,core::dungeon::Room::Direction direction,
                  MoveConstraints constraints)
{

}

void MagicalDungeonLevelBuilder::buildEntrance(RoomPtr room, core::dungeon::Room::Direction direction){

}

void MagicalDungeonLevelBuilder::buildExit(RoomPtr room, Room::Direction direction) {

}

void MagicalDungeonLevelBuilder::buildItem (RoomPtr room) {

}

void MagicalDungeonLevelBuilder::buildCreature (std::shared_ptr<Room> room) {

}
