#include "game.h"
#include "core/dungeon/basic/basicdungeonlevelbuilder.h"
#include "core/dungeon/room.h"
#include <algorithm>
#include "core/dungeon/doorway.h"
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

    createExampleRooms();
    buildExampleDoorways();
    buildExampleItems();
    buildExampleCreatures();

}
void Game::createRandomLevel(const std::string &name, int width, int height){
    builder->buildDungeonLevel(name, width, height);
    level=builder->getDungeonLevel();
    buildRandomRooms(width*height);
    buildRandomDoorways();
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

// deletes the raw pointer to level (reduce memory leak)
void Game::clearLevel(){
    if(level!=nullptr){
        level =nullptr;
        delete level;
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
    //Builds random entrance
    buildRandomEntrance();
    //Builds random exit
    buildRandomExit();
    // Build Corner rooms
    buildCornerRooms();
    //build Non Corner rooms
    buildNonCornerRooms();
}

void Game::buildCornerRooms(){
    // a corner room only has two sides it can connect
    // and the constraint tells us a minimum of 1

    buildTopLeftCornerRoom();
    buildTopRightCornerRoom();
    buildBottomLeftCornerRoom();
    buildBottomRightCornerRoom();

}

void Game::buildNonCornerRooms(){
    // A non corner room has 5 cases
    // i. room is top row but not corner
    // ii. room is left row but not corner
    // iii.room is right row but not corner
    // iv. room is bottom row but not corner
    // v. room is non of the above making it around mid row

    // Build top&bottom room doorways
    buildTopRooms();
    buildBottomRooms();
    // Build left&right room doorways
    buildLeftRooms();
    buildRightRooms();
    // Build mid room doorways
    buildMidRooms();
}

void Game::buildTopLeftCornerRoom(){
    // Loop all through all rooms in level (by id)
    for (int id=1; id<=level->numberOfRooms(); id++){
        // check if rooom is corner room
        if(level->isCornerRoom(id)==true){
            //check if room is in top row
            if(level->isTopRoom(id)==true){
                // check if room is on the left side(so we know which direction we set our doorway)
                if(level->isLeftRoom(id)){
                    // Building the doorway
                    // since we dealing with 2 sides then get random number either 1(south) or 2 (east)
                    // since its a top left corner
                    Direction side=static_cast<Direction>(getRandomBtn(1,2));
                    Direction otherSide=(side==Direction::East)? Direction::South : Direction::East;
                    // get random number tht determine if we building
                    // minimum of 1 doorway or an extra doorway as well
                    int num=getRandomBtn(1,2); // random to determine case

                    // This will always happen on any roll(satisfies the constraint)
                    if(num==2||num==1){
                        buildRoomDoorway(id, side);
                    }
                    // the extra case
                    if(num==1){
                        buildRoomDoorway(id, otherSide);
                    }
                }

            }
        }
    }

}

void Game::buildTopRightCornerRoom(){
    // Loop all through all rooms in level (by id)
    for (int id=1; id<=level->numberOfRooms(); id++){
        // check if rooom is corner room
        if(level->isCornerRoom(id)==true){
            //check if room is in top row
            if(level->isTopRoom(id)==true){
                // check if room is on the right side(so we know which direction we set our doorway)
                if(level->isRightRoom(id)){
                    // Building the doorway
                    // since we dealing with 2 sides then get random number either 1(south) or 3 (west)
                    // since its a top left corner
                    Direction side=static_cast<Direction>(getRandomBtn(1,3));
                    Direction otherSide=(side==Direction::West)? Direction::South : Direction::West;
                    // get random number tht determine if we building
                    // minimum of 1 doorway or an extra doorway as well
                    int num=getRandomBtn(1,2); // random to determine case

                    // This will always happen on any roll(satisfies the constraint)
                    if(num==2||num==1){
                        buildRoomDoorway(id, side);
                    }
                    // the extra case
                    if(num==1){
                        buildRoomDoorway(id, otherSide);
                    }
                }
            }
        }
    }

}

void Game::buildBottomLeftCornerRoom(){
    // Loop all through all rooms in level (by id)
    for (int id=1; id<=level->numberOfRooms(); id++){
        // check if rooom is corner room
        if(level->isCornerRoom(id)==true){
            //check if room is in bottom row
            if(level->isBottomRoom(id)==true){
                // check if room is on the right side(so we know which direction we set our doorway)
                if(level->isLeftRoom(id)){
                    // Building the doorway
                    // since we dealing with 2 sides then get random number either 0(north) or 2 (east)
                    // since its a top left corner
                    Direction side=static_cast<Direction>(getRandomBtn(0,2));
                    Direction otherSide=(side==Direction::North)? Direction::East : Direction::North;
                    // get random number tht determine if we building
                    // minimum of 1 doorway or an extra doorway as well
                    int num=getRandomBtn(1,2); // random to determine case
                    // This will always happen on any roll(satisfies the constraint)
                    if(num==2||num==1){
                        buildRoomDoorway(id, side);
                    }
                    // the extra case
                    if(num==1){
                        buildRoomDoorway(id, otherSide);
                    }
                }

            }
        }
    }

}

void Game::buildBottomRightCornerRoom(){
    // Loop all through all rooms in level (by id)
    for (int id=1; id<=level->numberOfRooms(); id++){
        // check if rooom is corner room
        if(level->isCornerRoom(id)==true){
            //check if room is in bottom row
            if(level->isBottomRoom(id)==true){
                // check if room is on the right side(so we know which direction we set our doorway)
                if(level->isRightRoom(id)){
                    // Building the doorway
                    // since we dealing with 2 sides then get random number either 0(north) or 3 (west)
                    // since its a top left corner
                    Direction side=static_cast<Direction>(getRandomBtn(0,3));
                    Direction otherSide=(side==Direction::West)? Direction::North : Direction::West;
                    // get random number tht determine if we building
                    // minimum of 1 doorway or an extra doorway as well
                    int num=getRandomBtn(1,2); // random to determine case
                    // This will always happen on any roll(satisfies the constraint)
                    if(num==2||num==1){
                        buildRoomDoorway(id, side);
                    }
                    // the extra case
                    if(num==1){
                        buildRoomDoorway(id, otherSide);
                    }
                }
            }
        }
    }

}


void Game::buildTopRooms(){
    // for loop to check the ids of the rooms in the dungeon level
    for (int id=1; id<=level->numberOfRooms(); id++){
        // then check if there the id is that of a non-corner room
        if(level->isNonCornerRoom(id)==true){
            // then check if id is that of a room in the top side
            if(level->isTopRoom(id)==true){
                // Now we got our room,  time to build its doorways
                // we know if a room is on any side then it can only connect 3 ways (south, east and west)
                // we also do not need to check for entrance and exit here as this is not top or bottom xD

                int random=getRandomInt(1,2); // random number to determing the constraint cases
                // List of the available directions we can connect
                std::vector<Direction> list={Direction::South, Direction::East, Direction::West};
                std::random_shuffle(begin(list), end(list)); // shuffles the directions list (to make the options random not fixed)

                // the constraint states to include the entrance doorway if the room has entrance
                // this is considered in the last case. means it is bound to be included whether random number is 2(by default) or 3
                if(random==2){
                    buildRoomDoorway(id, list.at(0));
                }
                // will always happen
                if(random==2||random==1){
                    buildRoomDoorway(id, list.at(1));
                    // check if this room has entrance, it includes its available entrance door
                    // in the minimum value
                    if(level->retrieveRoom(id)->hasEntrance()==true){
                           // does nothing because we consider the entrance as the minimum among the 2
                    }else{
                        buildRoomDoorway(id, list.at(2));
                    }
                }
            }
        }
    }

}
void Game::buildBottomRooms(){
    // for loop to check the ids of the rooms in the dungeon level
    for (int id=1; id<=level->numberOfRooms(); id++){
        // then check if there the id is that of a non-corner room
        if(level->isNonCornerRoom(id)==true){
            // then check if id is that of a room in the bottom side
            if(level->isBottomRoom(id)==true){
                // Now we got our room,  time to build its doorways
                // we know if a room is on any side then it can only connect 3 ways (north, east and west)
                // we also do not need to check for entrance and exit here as this is not top or bottom xD

                int random=getRandomInt(1,2); // random number to determing the constraint cases
                // List of the available directions we can connect
                std::vector<Direction> list={Direction::North, Direction::East, Direction::West};
                std::random_shuffle(begin(list), end(list)); // shuffles the directions list (to make the options random not fixed)

                // the constraint states to include the exit doorway if the room has exit(occurs at bottom row)
                // this is considered in the last case. means it is bound to be included whether random number is 2 or 3
                if(random==2){
                    buildRoomDoorway(id, list.at(0));
                }
                // Always going to happen
                if(random==2||random==1){
                    buildRoomDoorway(id, list.at(1));
                    // check if this room has exit, it includes its available entrance door
                    // in the minimum value
                    if(level->retrieveRoom(id)->roomHasExit()==true){
                        // does nothing as we already consider the exit doorway as one of the minimum required of at least 2
                    }else{
                        buildRoomDoorway(id, list.at(2));
                    }

                }

            }
        }
    }
}
void Game::buildLeftRooms(){
    // for loop to check the ids of the rooms in the dungeon level
    for (int id=1; id<=level->numberOfRooms(); id++){
        // then check if there the id is that of a non-corner room
        if(level->isNonCornerRoom(id)==true){
            // then check if id is that of a room in the left side
            if(level->isLeftRoom(id)==true){
                // Now we got our room,  time to build its doorways
                // we know if a room is on any side then it can only connect 3 ways (north, south and east)
                // we also do not need to check for entrance and exit here as this is not top or bottom xD

                int random=getRandomInt(1,2); // random number to determing the constraint cases
                // List of the available directions we can connect
                std::vector<Direction> list={Direction::North, Direction::South, Direction::East};
                std::random_shuffle(begin(list), end(list)); // shuffles the directions list (to make the options random not fixed)
                if(random==2){
                    buildRoomDoorway(id, list.at(0));
                }
                // always happen
                if(random==2||random==1){
                    buildRoomDoorway(id, list.at(1));
                    buildRoomDoorway(id, list.at(2));
                }
            }
        }
    }
}
void Game::buildRightRooms(){
    // for loop to check the ids of the rooms in the dungeon level
    for (int id=1; id<=level->numberOfRooms(); id++){
        // then check if there the id is that of a non-corner room
        if(level->isNonCornerRoom(id)==true){
            // then check if id is that of a room in the right side
            if(level->isRightRoom(id)==true){
                // Now we got our room,  time to build its doorways
                // we know if a room is on any side then it can only connect 3 ways (north, south and west)
                // we also do not need to check for entrance and exit here as this is not top or bottom xD

                int random=getRandomInt(1,2); // random number to determing the constraint cases
                // List of the available directions we can connect
                std::vector<Direction> list={Direction::North, Direction::South, Direction::West};
                std::random_shuffle(begin(list), end(list)); // shuffles the directions list (to make the options random not fixed)
                if(random==2){
                    buildRoomDoorway(id, list.at(0));
                }
                if(random==2||random==1){
                    buildRoomDoorway(id, list.at(1));
                    buildRoomDoorway(id, list.at(2));
                }
            }
        }
    }
}
void Game::buildMidRooms(){
    for(int id=1; id<=level->numberOfRooms(); id++){
        if(level->isMidRoom(id)){
            // first we get a random number between 2 and 4
            // as we now we need a minimum of 2 connections and maximum of 4 connections for mid rooms
            int randNum=getRandomInt(1,3);
            // vector of 4 different random numbers 0-3 (used to cast to direction)
            std::vector<Direction> list={Direction::East,Direction::West, Direction::South, Direction::North};
            //reshuffle
            std::random_shuffle(begin(list), end(list));
            // We make cases


            // if 4 then build 4 doorways
            if(randNum==3){
                buildRoomDoorway(id,static_cast<Direction>(list.at(0)));
            }
            if(randNum==3||randNum==2){
                buildRoomDoorway(id,static_cast<Direction>(list.at(1)));
            }
            // case always happens
            if(randNum==3||randNum==2||randNum==1){
                // when any number rolls up then we must build 2 doorways unless there is a connection existing already
                // check if there is already a passage existing then we do nothing
                buildRoomDoorway(id,static_cast<Direction>(list.at(2)));
                buildRoomDoorway(id,static_cast<Direction>(list.at(3)));
            }
        }
    }
}


void Game::buildRandomEntrance(){
    // Since this class build entrance first there is no need to check if there is an exit
    // if check to see entranceID is that of a corner room or non-corner room
    // if true apply pick random direction choice

    int last=level->width();// length of the first row
    int start=1;           // first id will always be 1
    int entranceID=getRandomInt(start, last); // random id from first row

    // We must give the entrance a freedom or random any side when the width=1
    if(level->width()==1){
        // if height ==1 then we can chose any side to make entrance doorway
        if(level->height()==1){
            // assign the entrance anywhere at random
            builder->buildEntrance(level->retrieveRoom(entranceID), static_cast<Direction>(getRandomInt(0,3)));
        }else{
            // otherwise we can only assign north,east or west
            std::vector<Direction> list={Direction::North, Direction::East, Direction::West};
            // shuffle the list with directions
            std::random_shuffle(begin(list), end(list));
            // pick one at random
            builder->buildEntrance(level->retrieveRoom(entranceID), list.at(getRandomInt(0,2)));
        }
    }
    // if non of the case above occurs then we consider the normal approach below
    else{
        if(entranceID==start){ // if entrance id is equal to that of first corner
            // Direction either North or West (0 or 3)
            builder->buildEntrance(level->retrieveRoom(entranceID),static_cast<Direction>(getRandomBtn(0,3)));
        }else if(entranceID==last){
            // Direction either North or East
                builder->buildEntrance(level->retrieveRoom(entranceID),static_cast<Direction>(getRandomBtn(0,2)));
        }else{
            // Direction can only be North
            builder->buildEntrance(level->retrieveRoom(entranceID),Direction::North);
        }
    }
}

void Game::buildRandomExit(){
    // we know the last id = level->numberOfrooms()
    // the first id in last row= lastId-width+1
    int end=level->numberOfRooms();
    int begin=end-(level->width()) +1;
    // we get a random number that represents a random id picked from the last row
    int randId=getRandomInt(begin, end);

    // we must consider a case where width =1
    if(level->width()==1){
        // also consider if height =1 (1x1 dungeon)
        if(level->height()==1){
            // pick random direction 0-3
            Direction random=static_cast<Direction>(getRandomInt(0,3));
            // build an entrance at that edge/direction, but first check if there is already an entrance
            if(std::dynamic_pointer_cast<core::dungeon::Doorway>(level->retrieveRoom(randId)->edgeAt(random))){
                if(std::dynamic_pointer_cast<core::dungeon::Doorway>(level->retrieveRoom(randId)->edgeAt(random))->isEntrance()){
                    // attempt to build the exit again until it does not happen
                    buildRandomExit(); //recursion
                }
            }
            //otherwise just build an exit doorway here
            builder->buildExit(level->retrieveRoom(randId), random);
            return;// end the function to avoid any further execution
        }
        // otherwise the height is greater than 1 we can also build exit at south, east or west(1-3)
        builder->buildExit(level->retrieveRoom(randId), static_cast<Direction>(getRandomInt(1,3)));
    }else{
        // check if the random id is that of a corner room (begin and end are corner ids already)
        if(randId==begin){ //first corner at the bottom
            // Direction either south or west(get random number either 1 or 3)
            builder->buildExit(level->retrieveRoom(randId),static_cast<Direction>(getRandomBtn(1,3)));
        }else if(randId==end){// check if random id is that of right corner
            // Direction either south or east ( 1 or 2)
            builder->buildExit(level->retrieveRoom(randId),static_cast<Direction>(getRandomBtn(1,2)));
        }else{
            // Otherwise randId isnt that of a corner room thus direction can only be south
            builder->buildExit(level->retrieveRoom(randId),Direction::South);
        }
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

DLB::MoveConstraints Game::getConstraint(){
    // constraint for the origin doorway
    MoveConstraints originC;
    // constraint for the destination room doorway
    MoveConstraints destC;

    originC=builder->getRandomOriginConstraint();
    destC=builder->getRandomDestConstraint();
    // general constraint set is returned(individual constraints added together)
    return originC|destC;
}

void Game::buildRoomDoorway(int id, Direction side){
    // check if there is a connection existing
    if((level->retrieveRoom(id)->edgeAt(side)->isPassage())==true){

    }else{
        builder->buildDoorway(level->retrieveRoom(id), level->retrieveNearbyRoom(id,side),side,getConstraint());
    }

}

