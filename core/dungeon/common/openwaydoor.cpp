#include "openwaydoor.h"
using namespace core::dungeon::common;
OpenWayDoor::OpenWayDoor()
{

}


bool OpenWayDoor::isPassage() const{
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
