#include "lockeddoorway.h"
using namespace core::dungeon::common;
LockedDoorway::LockedDoorway()
{

}

bool LockedDoorway::isPassage() const{
    return (opposite) ? true : false;
}

std::string LockedDoorway::description() const{}
char LockedDoorway::displayCharacter() const{}
