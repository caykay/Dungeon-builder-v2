#include "basicdungeonlevelbuilder.h"
#include "quartzchamber.h"
#include "rockchamber.h"
#include "core/game.h"

using namespace core::dungeon::basic;
using Room= core::dungeon::Room;
using RoomPtr=std::shared_ptr<Room>;
using Direction=Room::Direction;
using DoorWay=core::dungeon::Doorway;
using OpenDoorWay=core::dungeon::common::OpenDoorWay;
using LockedDoorWay=core::dungeon::common::LockedDoorway;
using OneWayDoor=core::dungeon::common::OneWayDoor;
using BlockedDoorWay=core::dungeon::common::BlockedDoorway;
using DBL= core::dungeon::DungeonLevelBuilder;


BasicDungeonLevelBuilder::BasicDungeonLevelBuilder()
{

}

void BasicDungeonLevelBuilder::buildDungeonLevel(const std::string &name, int width, int height) {
    _level=new BasicDungeonLevel(name, width, height);
    createPrototypeItems();
    createPrototypeCreatures();
}

int BasicDungeonLevelBuilder::getRandomInt(int min, int max){
    // no need to generate random number
    if (min==max){
        return max;
    }
    if (max < min){
        std::swap(min,max);
    }

    return (int)(core::Game::instance().randomDouble() * (max-min +1)) + min;
}

RoomPtr BasicDungeonLevelBuilder::buildRoom(int id)  {
    //random generation;

    int randomNumber= getRandomInt(1,4);
    switch (randomNumber) {
    case 1|2|3:
        // 75% of the time
        return std::make_shared<QuartzChamber>(id);
        break;
    default:
        // rare case 25% of the time
        return std::make_shared<RockChamber>(id);
        break;
    }
}

void BasicDungeonLevelBuilder::buildDoorway(RoomPtr origin, RoomPtr destination,Direction direction,
                  DBL::MoveConstraints constraints)
{
    // TODO remove 1
    std::shared_ptr<DoorWay> originDoorway;
    std::shared_ptr<DoorWay> destinationDoorway;
    // checks if the constraint has an originlocked bit
    if((constraints&MoveConstraints::OriginLocked)==(MoveConstraints::OriginLocked)){
        // sets the origin door variable to a locked Doorway
        originDoorway=std::make_shared<LockedDoorWay>();
        // checks if the constraint has destination locked bit
        if((constraints&MoveConstraints::DestinationLocked)==(MoveConstraints::DestinationLocked)){
            // sets the destination doorway to a locked door
            destinationDoorway=std::make_shared<LockedDoorWay>();
            // Set opposite doorways
            originDoorway->connect(destinationDoorway.get());
            destinationDoorway->connect(originDoorway.get());
            //set origin and destination rooms edges
            origin->setEdge(originDoorway, direction);
            destination->setEdge(destinationDoorway, opposite(direction));

        }
        // Checks if the constraint has a Destingation impassable bit
        else if((constraints&MoveConstraints::DestinationImpassable)==(MoveConstraints::DestinationImpassable)){
            destinationDoorway=std::make_shared<OneWayDoor>();
            // Set opposite doorways
            originDoorway->connect(destinationDoorway.get());
            destinationDoorway->connect(originDoorway.get());
            //set origin and destination rooms edges
            origin->setEdge(originDoorway, direction);
            destination->setEdge(destinationDoorway, opposite(direction));

        }
        // Otherwise the destination door is an Open doorway
        else{
            // construct pointers the destination doorway as an OPenDoorWay
            destinationDoorway=std::make_shared<OpenDoorWay>();
            // Set opposite doorways
            originDoorway->connect(destinationDoorway.get());
            destinationDoorway->connect(originDoorway.get());
            //set origin and destination rooms edges
            origin->setEdge(originDoorway, direction);
            destination->setEdge(destinationDoorway, opposite(direction));
        }
    }
    // Checks if the constraints has an origin impassable bit
    else if((constraints&MoveConstraints::OriginImpassable)==(MoveConstraints::OriginImpassable)){

        if((constraints&MoveConstraints::DestinationLocked)==(MoveConstraints::DestinationLocked)){
            originDoorway=std::make_shared<OneWayDoor>();
            destinationDoorway=std::make_shared<LockedDoorWay>();
            // Set opposite doorways
            originDoorway->connect(destinationDoorway.get());
            destinationDoorway->connect(originDoorway.get());
            //set origin and destination rooms edges
            origin->setEdge(originDoorway, direction);
            destination->setEdge(destinationDoorway, opposite(direction));

        }else if ((constraints&MoveConstraints::DestinationImpassable)==(MoveConstraints::DestinationImpassable)){
            // sets both doors as blocked as adhered to the constraints
            originDoorway=std::make_shared<BlockedDoorWay>();
            destinationDoorway=std::make_shared<BlockedDoorWay>();
            // Set opposite doorways
            originDoorway->connect(destinationDoorway.get());
            destinationDoorway->connect(originDoorway.get());
            //set origin and destination rooms edges
            origin->setEdge(originDoorway, direction);
            destination->setEdge(destinationDoorway, opposite(direction));

        }else{
            originDoorway=std::make_shared<OneWayDoor>();
            // construct pointers the destination doorway as an OPenDoorWay
            destinationDoorway=std::make_shared<OpenDoorWay>();
            // Set opposite doorways
            originDoorway->connect(destinationDoorway.get());
            destinationDoorway->connect(originDoorway.get());
            //set origin and destination rooms edges
            origin->setEdge(originDoorway, direction);
            destination->setEdge(destinationDoorway, opposite(direction));

        }
    }
    // Otherwise the origin constraint is not set therefore maps open dooorway
    else{
        // construct pointers to two OPenDoorWays
        originDoorway=std::make_shared<OpenDoorWay>();
        // checks if the constraint has destination locked bit
        if((constraints&MoveConstraints::DestinationLocked)==(MoveConstraints::DestinationLocked)){
            // sets the destination doorway to a locked door
            destinationDoorway=std::make_shared<LockedDoorWay>();
            // Set opposite doorways
            originDoorway->connect(destinationDoorway.get());
            destinationDoorway->connect(originDoorway.get());
            //set origin and destination rooms edges
            origin->setEdge(originDoorway, direction);
            destination->setEdge(destinationDoorway, opposite(direction));

        }
        // Checks if the constraint has a Destingation impassable bit
        else if((constraints&MoveConstraints::DestinationImpassable)==(MoveConstraints::DestinationImpassable)){
            destinationDoorway=std::make_shared<OneWayDoor>();
            // Set opposite doorways
            originDoorway->connect(destinationDoorway.get());
            destinationDoorway->connect(originDoorway.get());
            //set origin and destination rooms edges
            origin->setEdge(originDoorway, direction);
            destination->setEdge(destinationDoorway, opposite(direction));

        }
        // Otherwise the constraints is a 0 constraint meaning construction of two open doorways
        else{
            // construct pointers the destination doorway as an OPenDoorWay
            destinationDoorway=std::make_shared<OpenDoorWay>();
            // Set opposite doorways
            originDoorway->connect(destinationDoorway.get());
            destinationDoorway->connect(originDoorway.get());
            //set origin and destination rooms edges
            origin->setEdge(originDoorway, direction);
            destination->setEdge(destinationDoorway, opposite(direction));
        }
    }
}

void BasicDungeonLevelBuilder::buildEntrance(RoomPtr room, Room::Direction direction){
    // the false is for exit and true is for entrance bools
    std::shared_ptr<DoorWay> entrance = std::make_shared<OpenDoorWay>('i');
    room->setEdge(entrance, direction);
}

void BasicDungeonLevelBuilder::buildExit(RoomPtr room, Room::Direction direction) {
    // the true is for exit and false is for entrance bools
    std::shared_ptr<DoorWay> exit = std::make_shared<OpenDoorWay>('x');
    room->setEdge(exit, direction);
}

void BasicDungeonLevelBuilder::buildItem (RoomPtr room) {
    room->setItem(getRandomItem());
}

void BasicDungeonLevelBuilder::buildCreature (std::shared_ptr<Room> room) {
    room->setCreature(getRandomCreature());
}

core::dungeon::DungeonLevel* BasicDungeonLevelBuilder::getDungeonLevel(){
    return _level;
}

Room::Direction BasicDungeonLevelBuilder::opposite(Direction direction){
    switch (direction) {
    case Direction::North:
        return Direction::South;
        break;
    case Direction::South:
        return Direction::North;
        break;
    case Direction::East:
        return Direction::West;
        break;
    case Direction::West:
        return Direction::West;
        break;
    }
}



void BasicDungeonLevelBuilder::createPrototypeItems(){
    prototypeItems[Items::Boomerang]= new core::items::Weapon("Boomerang");
    prototypeItems[Items::Battle_Axe]= new core::items::Weapon("Battle Axe");
    prototypeItems[Items::Short_Sword]=new core::items::Weapon("Short Staff");
    prototypeItems[Items::Smoke_Bomb]=new core::items::Weapon("Smoke Bomb");
    prototypeItems[Items::Health_Potion]=new core::items::Weapon("Health Potion");
    prototypeItems[Items::Molotov_Cocktail]=new core::items::Weapon("Molotov Cocktail");
}

void BasicDungeonLevelBuilder::createPrototypeCreatures(){
    prototypeCreatures[Monsters::Goblin]= std::make_unique<core::creatures::Monster>("Goblin");
    prototypeCreatures[Monsters::Werewolf]= std::make_unique<core::creatures::Monster>("Werewold");
    prototypeCreatures[Monsters::Evil_Wizard]= std::make_unique<core::creatures::Monster>("Evil Wizard");
}
core::items::Item *BasicDungeonLevelBuilder::createItem(Items item) {

    return prototypeItems[(Items)item]->clone();
}

std::unique_ptr<core::creatures::AbstractCreature> BasicDungeonLevelBuilder::createMonster(Monsters monster){
    return prototypeCreatures[monster]->clone();
}

std::unique_ptr<core::items::Item> BasicDungeonLevelBuilder::getRandomItem(){
    int randomNum=getRandomInt(1,6);
    switch (randomNum) {
    case 1:
        return std::unique_ptr<core::items::Item>{createItem(Items::Boomerang)};
        break;
    case 2:
        return std::unique_ptr<core::items::Item>{createItem(Items::Battle_Axe)};
        break;
    case 3:
        return std::unique_ptr<core::items::Item>{createItem(Items::Short_Sword)};
        break;
    case 4:
        return std::unique_ptr<core::items::Item>{createItem(Items::Health_Potion)};
        break;
    case 5:
        return std::unique_ptr<core::items::Item>{createItem(Items::Molotov_Cocktail)};
        break;
    default:
        return std::unique_ptr<core::items::Item>{createItem(Items::Smoke_Bomb)};
        break;
    }
}

std::shared_ptr<core::creatures::AbstractCreature> BasicDungeonLevelBuilder::getRandomCreature(){
    int randomNum=getRandomInt(1,3);
    switch (randomNum) {
    case 1:
        return createMonster(Monsters::Goblin);
        break;
    case 2:
        return createMonster(Monsters::Werewolf);
        break;
    default:
        return createMonster(Monsters::Evil_Wizard);
        break;
    }
}

bool operator ==(DBL::MoveConstraints constraint1,DBL::MoveConstraints constraint2){
    return static_cast<DBL::MoveConstraints>(constraint1)==static_cast<DBL::MoveConstraints>(constraint2);
}

