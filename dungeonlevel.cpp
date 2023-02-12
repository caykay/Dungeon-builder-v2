#include "dungeonlevel.h"
#include <sstream>
using namespace core::dungeon;
DungeonLevel::DungeonLevel()
{

}
DungeonLevel::DungeonLevel(const std::string &name, int width, int height){
    levelName=name;
    levelWidth=width;
    levelHeight=height;
}


bool DungeonLevel::addRoom(std::shared_ptr<Room> room){
    // fetch the most recent id in the rooms map
    int lastId=getLastID();
    // new id is incremented by 1
    int newId=lastId+1;
    // checks if the rooms map is full
    if(newId<=(levelHeight*levelWidth)){
        rooms[newId]=room;
        return true;
    }else{
        return false;
    }
}
std::shared_ptr<Room> DungeonLevel::retrieveRoom (int id){
    return rooms[id];
}
int DungeonLevel::width() const{
    return levelWidth;
}
int DungeonLevel::height() const{
    return levelHeight;
}
int DungeonLevel::numberOfRooms() const{
    return width()*height();
}
std::string DungeonLevel::name() const{
    return levelName;
}


std::vector<std::string> DungeonLevel::display(){

    return getDungeonRows();
}

std::vector<std::string> DungeonLevel::getDungeonRows(){
    std::vector<std::string> rows;
    int id=1;
    for(int k=1; k<=height(); k++){
        // for each string in room (we picked the first room as all rooms have same size)
        for(int j=0; j<(int)rooms[1]->display().size(); j++){
            // this string stores and concatenates string of every row of room
            std::stringstream a;
            // Then loop along the width row
            for(int i=1; i<=width(); i++){
                // concatenate first string
                a<<rooms[id]->display().at(j);

                // check if we are at the last room in the row
                // so that we do not need to apply the "--" or empty space
                if(i!=width()){
                    // check if we are at mid position of room
                    if(j==2){
                        // check if this room has a connection to the right(east)
                        if(rooms[id]->edgeAt(Room::Direction::East)->isPassage()==true){
                            a<<"--";
                        }else{
                            a<<"  ";
                        }
                    }else{
                        a<<"  ";
                    }
                }
                // increment id to reference next door int row
                id+=1;
            }
            // push the stringstream of a row as the first string of the room display
            rows.push_back(a.str());
            // decrement the id to reference the begining of a row so that we
            // start concatenating the next string in display
            id-=width();
        }
        // for loop to check connection with rooms below
        std::stringstream b;
        int count=0; // count that checks the number of connections
        for(int i=1; i<=width(); i++){
            // check if room has a passage with below room(south)
            if(rooms[id]->edgeAt(Room::Direction::South)->isPassage()==true){
                b<<"     |     ";
                count++;
            }else{
                b<<"           ";
            }
            b<<"  ";
            // increment id
            id+=1;
        }
        // check if count >0
        if(count>0){
            rows.push_back(b.str());
        }

        // from the above incrementation id is expected to be incremented to reference
        // the room of the beginning of the next row
    }

    return rows;
}


int DungeonLevel::getLastID(){
    return rooms.size();
}

std::shared_ptr<Room> DungeonLevel::retrieveNearbyRoom (int id, Room::Direction direction){

    switch (direction) {
    case Room::Direction::North:
        return retrieveRoom(id-width());
        break;
    case Room::Direction::South:
        return retrieveRoom(id+width());
        break;
    case Room::Direction::East:
        return retrieveRoom(id+1);
    break;
    case Room::Direction::West:
        return retrieveRoom(id-1);
    break;
    }
}


std::vector<int> DungeonLevel::getFirstRowIDs(){
    // cointains ids of the rooms in the first row
    std::vector<int> firstRow;
    // fils up the first row with room ids
    for(int id=1; id<=width(); id++){
        firstRow.push_back(id);
    }
    return firstRow;
}
std::vector<int> DungeonLevel::getLastRowIDs(){
    // contains ids of the rooms in the last row
    std::vector<int> lastRow;
    // fills up the last row with room ids
    int i=numberOfRooms(); //gets the ids from last room
                                      // then decrements from there
    for (int id=i-width()+1; id<=numberOfRooms(); id++){
        lastRow.push_back(id);
    }
    return lastRow;
}


std::vector<int> DungeonLevel::getCornerRoomIds(){
    std::vector<int> lastRow=getLastRowIDs();
    std::vector<int> firstRow=getFirstRowIDs();
    std::vector<int> corners;
    // in most cases a room can have a maximum of 4 corners
    int corner1 = firstRow.at(0);
    corners.push_back(corner1);
    int corner2 =firstRow.at(firstRow.size()-1);
    corners.push_back(corner2);
    int corner3 = lastRow.at(0);
    corners.push_back(corner3);
    int corner4 =lastRow.at(lastRow.size()-1);
    corners.push_back(corner4);

    return corners;
}

std::vector<int> DungeonLevel::getNonCornerRoomIds(){
    std::vector<int> corners=getCornerRoomIds();
    std::vector<int> nonCorners;

    for(int j=1; j<=(width()*height());j++){
        for(int i=0;i<(int)corners.size(); i++){
            if(j!=corners.at(i)){
                nonCorners.push_back(j);
            }
        }
    }
    return nonCorners;
}

std::vector<int> DungeonLevel::getLeftRoomIds(){
    std::vector<int> lastRow=getLastRowIDs();
    std::vector<int> firstRow=getFirstRowIDs();
    std::vector<int> leftRooms;

    int corner1 = firstRow.at(0);
    int corner3 = lastRow.at(0);

    for (int i=corner1; i<=corner3; i+=width()){
        leftRooms.push_back(i);
    }

    return leftRooms;
}
// gets the ids or rooms aligned to the right including corner rooms
std::vector<int> DungeonLevel::getRightRoomIds(){
    std::vector<int> lastRow=getLastRowIDs();
    std::vector<int> firstRow=getFirstRowIDs();
    std::vector<int> rightRooms;

    int corner2 = firstRow.at(firstRow.size()-1);
    int corner4 = lastRow.at(lastRow.size()-1);

    for (int i=corner2; i<=corner4; i+=width()){
        rightRooms.push_back(i);
    }
    return rightRooms;
}

std::vector<int> DungeonLevel::getMidRoomIds(){
    std::vector<int> midRooms;
    // we have to check if the room is not on the top rows, bottom, left or right
    // then we know it belongs mid
    for (int id=1; id<=(width()*height());id++ ){
        if(isLeftRoom(id)==false){
            if(isRightRoom(id)==false){
                if(isTopRoom(id)==false){
                    if(isBottomRoom(id)==false){
                        midRooms.push_back(id);
                    }
                }
            }
        }
    }
    return midRooms;
}

bool DungeonLevel::isLeftRoom(int id){
    // does  include corner rooms
    std::vector<int> leftRooms=getLeftRoomIds();

    for(int k=0;k<(int)leftRooms.size(); k++){
        if(id==leftRooms.at(k)){
            return true;
        }
    }
    return false;
}
bool DungeonLevel::isRightRoom(int id){
    // does  include corner rooms
    std::vector<int> rightRooms= getRightRoomIds();
    for(int k=0;k<(int)rightRooms.size(); k++){
        if(id==rightRooms.at(k)){
            return true;
        }
    }
    return false;

}
bool DungeonLevel::isTopRoom(int id){
    // may include the corner rooms as well
    std::vector<int> topRooms= getFirstRowIDs();
    for(int k=0;k<(int)topRooms.size(); k++){
        if(id==topRooms.at(k)){
            return true;
        }
    }
    return false;

}
bool DungeonLevel::isBottomRoom(int id){
    // this may include the corner rooms as well
    std::vector<int> bottomRooms= getLastRowIDs();
    for(int k=0;k<(int)bottomRooms.size(); k++){
        if(id==bottomRooms.at(k)){
            return true;
        }
    }
    return false;

}

bool DungeonLevel::isMidRoom(int id){
    // no corner rooms or side rooms
    std::vector<int> midRooms= getMidRoomIds();
    for(int k=0;k<(int)midRooms.size(); k++){
        if(id==midRooms.at(k)){
            return true;
        }
    }
    return false;

}

bool DungeonLevel::isCornerRoom(int id){
    std::vector<int> corners= getCornerRoomIds();
    for(int k=0;k<(int)corners.size(); k++){
        if(id==corners.at(k)){
            return true;
        }
    }
    return false;

}

bool DungeonLevel::isNonCornerRoom(int id){
    if(isCornerRoom(id)==true){
        return false;
    }else{
        return true;
    }
}
