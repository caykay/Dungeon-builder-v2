#include "lockeddoorway.h"
using namespace core::dungeon::common;
LockedDoorway::LockedDoorway()
{

}

bool LockedDoorway::isPassage() const{
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
