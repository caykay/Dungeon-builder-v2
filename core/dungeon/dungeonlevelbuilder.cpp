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

void DungeonLevelBuilder::createPrototypeItems(){
    prototypeItems[Items::Boomerang]= std::make_unique<core::items::Weapon>(new core::items::Weapon("Boomerang"));
    prototypeItems[Items::Battle_Axe]= std::make_unique<core::items::Weapon>(new core::items::Weapon("Battle Axe"));
    prototypeItems[Items::Magic_Wand]=std::make_unique<core::items::Weapon>(new core::items::Weapon("Magic Sword"));
    prototypeItems[Items::Short_Sword]=std::make_unique<core::items::Weapon>(new core::items::Weapon("Short Staff"));
    prototypeItems[Items::Wizard_Staff]=std::make_unique<core::items::Weapon>(new core::items::Weapon("Wizard Staff"));
    prototypeItems[Items::Smoke_Bomb]=std::make_unique<core::items::Consumeable>(new core::items::Consumeable("Smoke Bomb"));
    prototypeItems[Items::Health_Potion]=std::make_unique<core::items::Consumeable>(new core::items::Consumeable("Health Potion"));
    prototypeItems[Items::Molotov_Cocktail]=std::make_unique<core::items::Consumeable>(new core::items::Consumeable("Molotov Cocktail"));
    prototypeItems[Items::Resistance_Potion]=std::make_unique<core::items::Consumeable>(new core::items::Consumeable("Resistance Potion"));
}

void DungeonLevelBuilder::createPrototypeCreatures(){
    prototypeCreatures[Monsters::Dragon]= std::make_unique<core::creatures::Monster>(new core::creatures::Monster("Dragon"));
    prototypeCreatures[Monsters::Goblin]= std::make_unique<core::creatures::Monster>(new core::creatures::Monster("Goblin"));
    prototypeCreatures[Monsters::Werewolf]= std::make_unique<core::creatures::Monster>(new core::creatures::Monster("Werewold"));
    prototypeCreatures[Monsters::Evil_Wizard]= std::make_unique<core::creatures::Monster>(new core::creatures::Monster("Evil Wizard"));
}
std::unique_ptr<core::items::Item> DungeonLevelBuilder::createItem(Items item){
    return prototypeItems[item]->clone();//use move?
}

std::unique_ptr<core::creatures::AbstractCreature> DungeonLevelBuilder::createMonster(Monsters monster){
    return prototypeCreatures[monster]->clone();//use move?
}

