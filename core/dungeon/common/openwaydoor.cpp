#include "openwaydoor.h"
using namespace core::dungeon::common;
OpenWayDoor::OpenWayDoor()
{

}


bool OpenWayDoor::isPassage() const{
    return (opposite) ? true : false;
}

std::string OpenWayDoor::description() const{}
char OpenWayDoor::displayCharacter() const{}
