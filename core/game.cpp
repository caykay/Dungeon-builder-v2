#include "game.h"
#include "core/dungeon/basic/basicdungeonlevelbuilder.h"
#include "core/dungeon/room.h"
//#include "menuinterface.h"
using namespace core;
using BasicDLB=core::dungeon::basic::BasicDungeonLevelBuilder;
std::unique_ptr<Game> Game::_theInstance;
double Game::randomDouble() {
  return _realDistribution(_randomGenerator);
}

void Game::setDungeonType(DLB* builder){

}
void Game::createExampleLevel(){
    builder=new BasicDLB();
    builder->buildDungeonLevel("Example Dungeon Level", 3, 3);
    level=builder->getDungeonLevel();
    //TODO Here
    createExampleRooms();
    buildExampleDoorways();
    buildExampleItems();
    buildExampleCreatures();
//    addRoomsToExampleLevel();

}
void Game::createRandomLevel(const std::string &name, int width, int height){

}

void Game::displayLevel(std::ostream &display){
    for (std::string row : level->display()){
        display<<row<<std::endl;
    }
}

void Game::describeLevel(std::ostream &display){
    display<<level->description();
}

void Game::describeRoom(std::ostream &display, int id){
    Room room=level->retrieveRoom(id);
    display<<room->description()<<std::endl;
}


Game &Game::instance(){
    if (!_theInstance){
        _theInstance .reset(new Game());
    }

    return *_theInstance;

}

void Game::createExampleRooms(){

    level->addRoom(builder->buildRoom(1));
    level->addRoom(builder->buildRoom(2));
    level->addRoom(builder->buildRoom(3));
    level->addRoom(builder->buildRoom(4));
    level->addRoom(builder->buildRoom(5));
    level->addRoom(builder->buildRoom(6));
    level->addRoom(builder->buildRoom(7));
    level->addRoom(builder->buildRoom(8));
    level->addRoom(builder->buildRoom(9));

}
void Game::buildExampleDoorways(){
    builder->buildEntrance(level->retrieveRoom(1), Direction::North);
    builder->buildDoorway(level->retrieveRoom(1), level->retrieveRoom(2), Direction::East, MoveConstraints::None);
    builder->buildDoorway(level->retrieveRoom(1), level->retrieveRoom(4), Direction::South, MoveConstraints::DestinationImpassable);
    builder->buildDoorway(level->retrieveRoom(2), level->retrieveRoom(3), Direction::East, MoveConstraints::OriginImpassable|MoveConstraints::DestinationImpassable);
    builder->buildDoorway(level->retrieveRoom(2), level->retrieveRoom(5), Direction::South, MoveConstraints::None);
    builder->buildDoorway(level->retrieveRoom(3), level->retrieveRoom(6), Direction::South, MoveConstraints::DestinationLocked);
    builder->buildDoorway(level->retrieveRoom(4), level->retrieveRoom(5), Direction::East, MoveConstraints::DestinationImpassable);
    builder->buildDoorway(level->retrieveRoom(4), level->retrieveRoom(7), Direction::South, MoveConstraints::OriginImpassable|MoveConstraints::DestinationImpassable);
    builder->buildDoorway(level->retrieveRoom(5), level->retrieveRoom(8), Direction::South, MoveConstraints::None);
    builder->buildDoorway(level->retrieveRoom(5), level->retrieveRoom(6), Direction::East, MoveConstraints::None);
    builder->buildDoorway(level->retrieveRoom(7), level->retrieveRoom(8), Direction::East, MoveConstraints::OriginLocked|MoveConstraints::DestinationLocked);
    builder->buildDoorway(level->retrieveRoom(8), level->retrieveRoom(9), Direction::East, MoveConstraints::None);
    builder->buildExit(level->retrieveRoom(9), Direction::East);

}

void Game::buildExampleItems(){
    builder->buildItem(level->retrieveRoom(3));
    builder->buildItem(level->retrieveRoom(5));
    builder->buildItem(level->retrieveRoom(7));
}

void Game::buildExampleCreatures(){
    builder->buildCreature(level->retrieveRoom(3));
    builder->buildCreature(level->retrieveRoom(5));
    builder->buildCreature(level->retrieveRoom(9));
}

//void Game::addRoomsToExampleLevel(DL* level, std::vector<Room> rooms){
//    for (Room room:rooms){
//        level->addRoom(room);
//    }
//}
