#include "opendoorway.h"
using namespace core::dungeon::common;
OpenDoorWay::OpenDoorWay()
{

}

OpenDoorWay::OpenDoorWay(char state){
    switch (tolower(state)) {
    // entrance
    case 'i':
        entrance=true;
        character='I';
        break;
    // exit
    case 'x':
        exit=true;
        character='0';
        break;
    }
}
bool OpenDoorWay::isPassage() const{

    if (isExit()||isEntrance()==true){
        return false;
    }
    if (opposite!=nullptr){
        return true;
    }
    return false;


}

std::string OpenDoorWay::description() const{
    // check if doorway is an entrance door
    if(character=='I'){
        // display entrance message
        return "is an entrance door to the room and the dungeon and not";
    }
    // check if doorway is an exit door
    else if(character=='0'){
        return "is an exit door from the room and the dungeon and not";
    }else {
        return "is an Opendoor Doorway";
    }
}
char OpenDoorWay::displayCharacter() const{
    return character;
}

void OpenDoorWay::setCharacterAt(char direction) {
    switch (tolower(direction)) {
    case 'n':
        this->character='^';
        break;
    case 's':
        this->character='v';
        break;
    case 'e':
        this->character='>';
        break;
    case 'w':
        this->character='<';
        break;

    }

}
