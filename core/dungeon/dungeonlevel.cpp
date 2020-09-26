#include "dungeonlevel.h"
using namespace core::dungeon;
DungeonLevel::DungeonLevel()
{

}
DungeonLevel::DungeonLevel(const std::string &name, int width, int height){
    levelName=name;
    levelWidth=width;
    levelHeight=height;
}

//TODO add a check if room is already full
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
    // or just return width*height
    return rooms.size();
}
std::string DungeonLevel::name() const{
    return levelName;
}


std::vector<std::string> DungeonLevel::display(){
    std::vector<std::string> result;
    std::vector<std::string> rows=getDungeonRows();
    int count=0;
    for(std::string row : rows){
        if(row==""){
            count --;
        }else{
            result.push_back(row);
        }
        count++;
    }


    return result;
}
// TODO update this method: since we already have better helper methods to help reduce the size
std::vector<std::string> DungeonLevel::getDungeonRows(){
    std::vector<std::string> rows;
    //fill the rows with empty strings before concatenation
    int expectedRows=5*height()+(height()-1);// the expected number of rows
    for(int i=0;i<expectedRows; i++){
        rows.push_back("");
    }
    //m[i]=rooms[i]->display()
    int rowsDone=0; // this variable will keep track of the room string to be
                     // concatenated on a width row
    int colsDone=0;   // this variable will change the position to concatenate the next
                     // string in the final vector everytime we switch to new row
    // TODO not needed
    int numberOfRoomsInRow=numberOfRooms(); //proper implementation here pleas????????
    for(int k=1; k<=height();k++){
        // loops through rooms across the width
        for (int i=1; i<=width();i++){
            // TODO not needed
            int widthCheck;
            if(width()>numberOfRoomsInRow){
                widthCheck=numberOfRoomsInRow;
            }else{
                widthCheck=width();
            }
            // loops through the string in a room and concatenates with the
            // string at same position in adjacent room
            for(int j=0; j<(int)rooms[i+rowsDone]->display().size(); j++){
                std::string row1="";
                row1+=rooms[i+rowsDone]->display().at(j);
                // checks if the room is the last to be added widthwise
                if(i!=widthCheck){
                    if(j==2){
                        row1+="--";
                    }
                    else{row1+="  ";
                    }
                }

                rows.at(colsDone+j)+=row1;
            }
            // end row concatenation

        }
        // TODO not needed
        if(width()<numberOfRoomsInRow){
            numberOfRoomsInRow-=width();
        }

        // set the count to start from another row
        // on next iteration
        colsDone+=6;
        rowsDone+=width();

    }

    return rows;
}


int DungeonLevel::getLastID(){
    return rooms.size();
}

std::shared_ptr<Room> DungeonLevel::retrieveNearbyRoom (int id, Room::Direction direction){

    switch (direction) {
    case Room::Direction::North:
        return retrieveRoom(getAboveRoomId(id));
        break;
    case Room::Direction::South:
        return retrieveRoom(getBelowRoomId(id));
        break;
    case Room::Direction::East:
        return retrieveRoom(getRightRoomId(id));
    break;
    case Room::Direction::West:
        return retrieveRoom(getLeftRoomId(id));
    break;
    }
}

int DungeonLevel::getAboveRoomId(int id){
    return id-width();
}

int DungeonLevel::getBelowRoomId(int id){
    return id+width();
}

int DungeonLevel::getRightRoomId(int id){
    return id+1;
}

int DungeonLevel::getLeftRoomId(int id){
    return id-1;
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
    int id=numberOfRooms(); //gets the ids from last room
                                      // then decrements from there
    for (int i=width()-1; i>=0; i--){
        lastRow.push_back(id);
        id--;
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
