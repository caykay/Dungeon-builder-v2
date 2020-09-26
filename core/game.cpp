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

void Game::setDungeonType(char type){
    switch (tolower(type)) {
    case 'b':
        // set dungeon type to basicDungeon level builder
        setDungeonType(new BasicDLB());
        break;
    case 'm':
        // set dungeon type to magic dungeon level builder
        break;
    }
}

void Game::setDungeonType(DLB* builder){
    this->builder=builder;
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
    builder->buildDungeonLevel(name, width, height);
    level=builder->getDungeonLevel();
    buildRandomRooms(width*height);
     //buildRandomDoorways();
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

void Game::releaseInstance(){
    if(_theInstance!=nullptr){
//        _theInstance.reset(new Game());
        _theInstance=nullptr;
    }
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

void Game::buildRandomRooms(int size){
    for (int i=1; i<=size; i++){
        level->addRoom(builder->buildRoom(i));
    }
}

void Game::buildRandomDoorways(){
    std::vector<int> firstIds;
    std::vector<int> lastIds;
    int entranceID=getRandomId(firstIds); // random id from first row
    int exitID=getRandomId(lastIds); // random id from last row

    //Builds random entrance
    buildRandomEntrance(firstIds);
    //Builds random exit
    buildRandomExit(lastIds);
    // Build Corner rooms
    buildCornerRooms();
    //build Non Corner rooms
    buildNonCornerRooms();
    // TODO there's only one room then edge cant have both exit and entrance
    if(level->numberOfRooms()==1){

    }

}

void Game::buildCornerRooms(){
    // 1x1 case excluded (handleded with a different function)

}

void Game::buildNonCornerRooms(){
}

void Game::buildRandomEntrance(std::vector<int>firstIds){
    // if check to see entranceID is that of a corner room or non-corner room
    // if true apply pick random direction choice
    int entranceID=getRandomId(firstIds); // random id from first row

    int firstCorner=firstIds.at(0);
    int secondCorner=firstIds.at(firstIds.size()-1);
    if(entranceID==firstCorner){
        // Direction either North or West
        Direction direction=static_cast<Direction>(getRandomBtn(0,3));
        builder->buildEntrance(level->retrieveRoom(entranceID),direction);
    }else if(entranceID==secondCorner){
        // Direction either North or East
        Direction direction=static_cast<Direction>(getRandomBtn(0,2));
        builder->buildEntrance(level->retrieveRoom(entranceID),direction);

    }else{
        // Direction can only be North
        builder->buildEntrance(level->retrieveRoom(entranceID),Direction::North);
    }

}

void Game::buildRandomExit(std::vector<int> lastRowIDs){
    // if check to see exitID is that of a corner room or non-corner room
    // if true apply pick random direction choice
    int exitID=getRandomId(lastRowIDs); // random id from last row

    int firstCorner=lastRowIDs.at(0);
    int secondCorner=lastRowIDs.at(lastRowIDs.size()-1);
    if(exitID==firstCorner){
        // Direction either South or West
        Direction direction=static_cast<Direction>(getRandomBtn(1,3));
        builder->buildEntrance(level->retrieveRoom(exitID),direction);
    }else if(exitID==secondCorner){
        // Direction either South or East
        Direction direction=static_cast<Direction>(getRandomBtn(1,2));
        builder->buildEntrance(level->retrieveRoom(exitID),direction);

    }else{
        // Direction can only be South
        builder->buildEntrance(level->retrieveRoom(exitID),Direction::South);
    }

}


int Game::getRandomId(std::vector<int> list){
    int min=list.at(0);
    int max=0;
    for(int i :list){
        if (min>i){
            min=i;
        }
        if (max<i){
            max=i;
        }
    }
    return getRandomInt(min, max);
}

int Game::getRandomInt(int min, int max){
    // no need to generate random number
    if (min==max){
        return max;
    }
    if (max < min){
        std::swap(min,max);
    }

    return (int)(randomDouble() * (max-min +1)) + min;
}

int Game::getRandomBtn(int a, int b){
    int randNum=getRandomInt(1,2);
    switch (randNum) {
    case 1:
        return a;
        break;
    case 2:
        return b;
        break;
    }
}

DLB::MoveConstraints Game::getRandConstraint(){
    // constraint for the origin doorway
    MoveConstraints originC;
    // constraint for the destination room doorway
    MoveConstraints destC;

    int rand=getRandomInt(1,100);
    if(rand<=45){
        originC=destC=MoveConstraints::None;
    }else if(rand<=75){
        originC=MoveConstraints::OriginLocked;
        destC=MoveConstraints::DestinationLocked;
    }else{
        originC=MoveConstraints::OriginImpassable;
        destC=MoveConstraints::DestinationImpassable;
    }

    // general constraint set is returned(individual constraints added together)
    return originC|destC;
}

