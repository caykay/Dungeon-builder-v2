#include "blockeddoorway.h"
using namespace core::dungeon::common;
BlockedDoorway::BlockedDoorway()
{

}


bool BlockedDoorway::isPassage() const{
    return (opposite) ? true : false;
}



std::string BlockedDoorway::description() const{}
char BlockedDoorway::displayCharacter() const{}

