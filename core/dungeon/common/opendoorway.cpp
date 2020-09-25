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
        break;
    // exit
    case 'x':
        exit=true;
        break;
    }
}
bool OpenDoorWay::isPassage() const{
    if (isExit()||isEntrance()==true){
        return false;
    }else{
        return (opposite) ? true : false;
    }

}

std::string OpenDoorWay::description() const{
    return "is an Opendoor Doorway";
}
char OpenDoorWay::displayCharacter() const{
    if(isExit()==true&&isEntrance()==false){
        return '0';
    }else if(isEntrance()==true&&isExit()==false){
        return 'I';
    }

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
