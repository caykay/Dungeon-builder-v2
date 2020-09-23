#include "opendoorway.h"
using namespace core::dungeon::common;
OpenDoorWay::OpenDoorWay()
{

}

bool OpenDoorWay::isPassage() const{
    return (opposite) ? true : false;
}

std::string OpenDoorWay::description() const{}
char OpenDoorWay::displayCharacter() const{}
