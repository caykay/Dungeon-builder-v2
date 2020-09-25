#include "onewaydoor.h"
using namespace core::dungeon::common;
OneWayDoor::OneWayDoor()
{

}


bool OneWayDoor::isPassage() const{
    if (isExit()||isEntrance()==true){
        return false;
    }else{
        return (opposite) ? true : false;
    }

}

std::string OneWayDoor::description() const{
    return "is a Oneway Door";
}

char OneWayDoor::displayCharacter() const{
    return character;
}

void OneWayDoor::setCharacterAt(char direction) {
    switch (tolower(direction)) {
    case 'n':
        this->character='v';
        break;
    case 's':
        this->character='^';
        break;
    case 'e':
        this->character='<';
        break;
    case 'w':
        this->character='>';
        break;


    }

}
