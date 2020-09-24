#include "opendoorway.h"
using namespace core::dungeon::common;
OpenDoorWay::OpenDoorWay()
{

}

bool OpenDoorWay::isPassage() const{
    if (isExit()||isEntrance()==true){
        return false;
    }else{
        return (opposite) ? true : false;
    }

}

std::string OpenDoorWay::description() const{}
char OpenDoorWay::displayCharacter() const{
    return character;
}

void OpenDoorWay::setCharacterAt(const char &direction) {
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
