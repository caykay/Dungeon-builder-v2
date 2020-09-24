#include "dungeonlevel.h"
using namespace core::dungeon;
DungeonLevel::DungeonLevel()
{

}
DungeonLevel::DungeonLevel(const std::string &name, int width, int height){
    levelName=name;
    levelWidth=width;
    levelHeight=height;
    //populates the dungeon with empty rooms; UPDATE::We do not need this
    populateDungeon();
}

bool DungeonLevel::addRoom(std::shared_ptr<Room> room){
    // fetch the most recent id in the rooms map
    int lastId=getLastID();
    // new id is incremented by 1
    int newId=lastId=1;
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
    return rooms.size();
}
std::string DungeonLevel::name() const{
    return levelName;
}


std::vector<std::string> DungeonLevel::display(){
    std::vector<std::string> result;

    return result;
}

void DungeonLevel::populateDungeon(){
    int size=levelHeight*levelWidth;
    // populating the rooms map with empty rooms//nullptrs
    for (int i=1; i<=size; i++){
        rooms[i]=nullptr;
    }
}

int DungeonLevel::getLastID(){
    int count=1;

    int id=0;
    while (count<=(int)rooms.size()){
        if (rooms[count].get()==nullptr){
            id=count-1;
            // breaks as soon as a nullptr is encountered
            break;
        }

        count++;
    }

    // if 0 is returned then the rooms map is empty
    return id;
}
