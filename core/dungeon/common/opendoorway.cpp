#include "opendoorway.h"
using namespace core::dungeon::common;
OpenDoorWay::OpenDoorWay()
{

}

bool OpenDoorWay::isPassage() const{
    switch (opposite) {
    case 1:
        return true;
        break;
    case 0:
        return false;
        break;
    default:
        return false;
    }
}
