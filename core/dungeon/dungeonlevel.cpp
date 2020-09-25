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
    int numberOfRoomsInRow=numberOfRooms(); //proper implementation here pleas????????
    for(int k=1; k<=height();k++){
        // loops through rooms across the width
        for (int i=1; i<=width();i++){
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
