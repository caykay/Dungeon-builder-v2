#include "blockeddoorway.h"
using namespace core::dungeon::common;
BlockedDoorway::BlockedDoorway()
{

}

bool BlockedDoorway::isPassage() const{
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
