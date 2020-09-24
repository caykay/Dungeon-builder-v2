#include "dungeonlevelbuilder.h"
using namespace core::dungeon;
DungeonLevelBuilder::DungeonLevelBuilder()
{

}

void DungeonLevelBuilder::buildDungeonLevel(const std::string &name, int width, int height) {}
std::shared_ptr<Room> DungeonLevelBuilder::buildRoom(int id) {}
void DungeonLevelBuilder::buildDoorway(std::shared_ptr<Room> origin, std::shared_ptr<Room>destination,
                                       Room::Direction direction, MoveConstraints constraints) {}

void DungeonLevelBuilder::buildEntrance(std::shared_ptr<Room> room, Room::Direction direction) {}

void DungeonLevelBuilder::buildExit(std::shared_ptr<Room> room, Room::Direction direction) {}

void DungeonLevelBuilder::buildItem (std::shared_ptr<Room> room) {}

void DungeonLevelBuilder::buildCreature (std::shared_ptr<Room> room) {}

DungeonLevel* DungeonLevelBuilder::getDungeonLevel() {

}



//IMPLEMENTED IN CONCRETE BUILDERS
void DungeonLevelBuilder::createPrototypeItems(){
//    prototypeItems[Items::Boomerang]= std::make_unique<core::items::Weapon>("Boomerang");
//    prototypeItems[Items::Battle_Axe]= std::make_unique<core::items::Weapon>("Battle Axe");
//    prototypeItems[Items::Magic_Wand]=std::make_unique<core::items::Weapon>("Magic Sword");
//    prototypeItems[Items::Short_Sword]=std::make_unique<core::items::Weapon>("Short Staff");
//    prototypeItems[Items::Wizard_Staff]=std::make_unique<core::items::Weapon>("Wizard Staff");
//    prototypeItems[Items::Smoke_Bomb]=std::make_unique<core::items::Consumeable>("Smoke Bomb");
//    prototypeItems[Items::Health_Potion]=std::make_unique<core::items::Consumeable>("Health Potion");
//    prototypeItems[Items::Molotov_Cocktail]=std::make_unique<core::items::Consumeable>("Molotov Cocktail");
//    prototypeItems[Items::Resistance_Potion]=std::make_unique<core::items::Consumeable>("Resistance Potion");
}

void DungeonLevelBuilder::createPrototypeCreatures(){
//    prototypeCreatures[Monsters::Dragon]= std::make_unique<core::creatures::Monster>("Dragon");
//    prototypeCreatures[Monsters::Goblin]= std::make_unique<core::creatures::Monster>("Goblin");
//    prototypeCreatures[Monsters::Werewolf]= std::make_unique<core::creatures::Monster>("Werewold");
//    prototypeCreatures[Monsters::Evil_Wizard]= std::make_unique<core::creatures::Monster>("Evil Wizard");
}

std::shared_ptr<core::items::Item> DungeonLevelBuilder::createItem(Items item){
//    return  prototypeItems[item]->clone();//use move?
}

std::shared_ptr<core::creatures::AbstractCreature> DungeonLevelBuilder::createMonster(Monsters monster){
//    return prototypeCreatures[monster]->clone();//use move?
}

