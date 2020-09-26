#include "basicdungeonlevelbuilder.h"
#include "quartzchamber.h"
#include "rockchamber.h"
#include "core/game.h"
#include "core/dungeon/room.h"
#include "core/dungeon/roomedge.h"

using namespace core::dungeon::basic;
using Room= core::dungeon::Room;
using RoomPtr=std::shared_ptr<Room>;
using Direction=Room::Direction;
using DoorWay=core::dungeon::Doorway;
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
    // checks if the constraint has an originlocked bit
    if((constraints&MoveConstraints::OriginLocked)==(MoveConstraints::OriginLocked)){
        // Sets a locked doorway at the direction in origin room
        origin->setEdge(origin->createLockedDoorway(), direction);
        // checks if the constraint has destinationLocked constraint bit
        if((constraints&MoveConstraints::DestinationLocked)==(MoveConstraints::DestinationLocked)){
            // Sets a locked doorway at the direction in destination room
            destination->setEdge(destination->createLockedDoorway(), opposite(direction));
            connectDoors(origin, destination, direction);
        }
        // Checks if the constraint has a Destingation impassable bit
        else if((constraints&MoveConstraints::DestinationImpassable)==(MoveConstraints::DestinationImpassable)){
            // Sets a oneway doorway at the direction in destination room
            destination->setEdge(destination->createOnewaydoor(), opposite(direction));
            // Connects the doors
            connectDoors(origin, destination, direction);
        }
        // Otherwise the destination door is an Open doorway
        else{
            // Sets an open doorway at the direction in destination room
            destination->setEdge(origin->createOpenDoorway(), opposite(direction));
            // Connects the doors
            connectDoors(origin, destination, direction);
        }
    }
    // Checks if the constraints has an origin impassable bit
    else if((constraints&MoveConstraints::OriginImpassable)==(MoveConstraints::OriginImpassable)){

        if((constraints&MoveConstraints::DestinationLocked)==(MoveConstraints::DestinationLocked)){
            //set origin and destination rooms edges as both locked doorways
            origin->setEdge(origin->createOnewaydoor(), direction);
            destination->setEdge(destination->createLockedDoorway(), opposite(direction));

            // Connects the doors
            connectDoors(origin, destination, direction);

        }else if ((constraints&MoveConstraints::DestinationImpassable)==(MoveConstraints::DestinationImpassable)){
            //set origin and destination rooms edges as Blocked doorways
            origin->setEdge(origin->createBlockedDoorway(), direction);
            destination->setEdge(destination->createBlockedDoorway(), opposite(direction));

            // Connects the doors
            connectDoors(origin, destination, direction);

        }else{
            //Set the origin as impassable (one way door) and the destination as open doorway
            origin->setEdge(origin->createOnewaydoor(), direction);
            destination->setEdge(destination->createOpenDoorway(), opposite(direction));

            // Connects the doors
            connectDoors(origin, destination, direction);

        }
    }
    // Otherwise the origin constraint is not set therefore maps open dooorway
    else{
        // construct OPenDoorWay edge on the origin
        origin->setEdge(origin->createOpenDoorway(), direction);
        // checks if the constraint has destination locked bit
        if((constraints&MoveConstraints::DestinationLocked)==(MoveConstraints::DestinationLocked)){
            // Sets a locked doorway at the direction in destination room
            destination->setEdge(destination->createLockedDoorway(), opposite(direction));
            // Connects the doors
            connectDoors(origin, destination, direction);
        }
        // Checks if the constraint has a Destination impassable bit
        else if((constraints&MoveConstraints::DestinationImpassable)==(MoveConstraints::DestinationImpassable)){
            // Sets a one doorway(impassable) at the direction in destination room
            destination->setEdge(destination->createOnewaydoor(), opposite(direction));

            // Connects the doors
            connectDoors(origin, destination, direction);
         }
        // Otherwise the constraints is a 0 constraint meaning construction of two open doorways
        else{
            // Sets an open doorway at the direction in destination room
            destination->setEdge(destination->createOpenDoorway(), opposite(direction));
            // Connects the doors
            connectDoors(origin, destination, direction);
        }
    }
}

void BasicDungeonLevelBuilder::buildEntrance(RoomPtr room, Room::Direction direction){
    // Sets an open door way at the direction of the room, and specifies a character to
    // that represents the entrance character

    room->setEdge(room->createOpenDoorway('i'), direction);
}

void BasicDungeonLevelBuilder::buildExit(RoomPtr room, Room::Direction direction) {
    // Sets an open door way at the direction of the room, and specifies a character to
    // that represents the exit character

    room->setEdge(room->createOpenDoorway('x'), direction);
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

void BasicDungeonLevelBuilder::connectDoors(std::shared_ptr<Room> origin, std::shared_ptr<Room>destination, Room::Direction direction){
    // variable shared pointers linking to the origin and destination doors to be connected
    std::shared_ptr<DoorWay> originDoorway;
    std::shared_ptr<DoorWay> destinationDoorway;
    // definition of the above declared pointers
    originDoorway=std::dynamic_pointer_cast<Doorway>(origin->edgeAt(direction));
    destinationDoorway=std::dynamic_pointer_cast<Doorway>(destination->edgeAt(opposite(direction)));
    // sets opposite edges to ea other
    originDoorway->connect(destinationDoorway.get());
    destinationDoorway->connect(originDoorway.get());

}

bool operator ==(DBL::MoveConstraints constraint1,DBL::MoveConstraints constraint2){
    return static_cast<DBL::MoveConstraints>(constraint1)==static_cast<DBL::MoveConstraints>(constraint2);
}

