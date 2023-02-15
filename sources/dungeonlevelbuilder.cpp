#include "../headers/dungeonlevelbuilder.h"
using namespace core::dungeon;
DungeonLevelBuilder::DungeonLevelBuilder()
{
}

void DungeonLevelBuilder::buildDungeonLevel(const std::string &name, int width, int height) {}
std::shared_ptr<Room> DungeonLevelBuilder::buildRoom(int id) {}
void DungeonLevelBuilder::buildDoorway(std::shared_ptr<Room> origin, std::shared_ptr<Room> destination,
                                       Room::Direction direction, MoveConstraints constraints) {}

void DungeonLevelBuilder::buildEntrance(std::shared_ptr<Room> room, Room::Direction direction) {}

void DungeonLevelBuilder::buildExit(std::shared_ptr<Room> room, Room::Direction direction) {}

void DungeonLevelBuilder::buildItem(std::shared_ptr<Room> room) {}

void DungeonLevelBuilder::buildCreature(std::shared_ptr<Room> room) {}

DungeonLevel *DungeonLevelBuilder::getDungeonLevel()
{
}

// IMPLEMENTED IN CONCRETE BUILDERS
void DungeonLevelBuilder::createPrototypeItems()
{
}

void DungeonLevelBuilder::createPrototypeCreatures()
{
}

std::unique_ptr<core::items::Item> DungeonLevelBuilder::createItem(Items item)
{
}

std::unique_ptr<core::creatures::AbstractCreature> DungeonLevelBuilder::createMonster(Monsters monster)
{
}

std::shared_ptr<core::items::Item> DungeonLevelBuilder::getRandomItem() {}
std::shared_ptr<core::creatures::AbstractCreature> DungeonLevelBuilder::getRandomCreature() {}

// sets a random individual constraint for a doorway
DungeonLevelBuilder::MoveConstraints DungeonLevelBuilder::getRandomOriginConstraint() {}
DungeonLevelBuilder::MoveConstraints DungeonLevelBuilder::getRandomDestConstraint() {}
