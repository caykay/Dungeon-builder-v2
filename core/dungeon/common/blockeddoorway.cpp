#include "blockeddoorway.h"
using namespace core::dungeon::common;
BlockedDoorway::BlockedDoorway()
{

}


bool BlockedDoorway::isPassage() const{
    // This wont matter because a blocked doorway is not expected to be an entrance or exit
    if (isExit()||isEntrance()==true){
        return false;
    }
    if (opposite!=nullptr){
        return true;
    }
    return false;

}



std::string BlockedDoorway::description() const{
    return "is a Blocked Doorway";
}
char BlockedDoorway::displayCharacter() const{
    return 'X';
}

void BlockedDoorway::setCharacterAt(char direction) {
}


