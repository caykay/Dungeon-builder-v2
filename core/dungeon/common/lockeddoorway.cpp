#include "lockeddoorway.h"
using namespace core::dungeon::common;
LockedDoorway::LockedDoorway()
{

}

bool LockedDoorway::isPassage() const{
    if (isExit()||isEntrance()==true){
        return false;
    }else{
        return (opposite) ? true : false;
    }

}

std::string LockedDoorway::description() const{}

char LockedDoorway::displayCharacter() const{
    return '@';
}

void LockedDoorway::setCharacterAt(const char &direction) {
}
