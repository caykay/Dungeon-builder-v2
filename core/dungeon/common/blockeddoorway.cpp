#include "blockeddoorway.h"
using namespace core::dungeon::common;
BlockedDoorway::BlockedDoorway()
{

}


bool BlockedDoorway::isPassage() const{
    // This wont matter because a blocked doorway is not expected to be an entrance or exit
    if (isExit()||isEntrance()==true){
        return false;
    }else{
        return (opposite) ? true : false;
    }

}



std::string BlockedDoorway::description() const{}
char BlockedDoorway::displayCharacter() const{
    return 'X';
}

void BlockedDoorway::setCharacterAt(const char &direction) {
}


