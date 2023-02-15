#include "../headers/lockeddoorway.h"
using namespace core::dungeon::common;
LockedDoorway::LockedDoorway()
{
}

bool LockedDoorway::isPassage() const
{
    if (isExit() || isEntrance() == true)
    {
        return false;
    }
    if (opposite != nullptr)
    {
        return true;
    }
    return false;
}

std::string LockedDoorway::description() const
{
    return "is a Locked Doorway";
}

char LockedDoorway::displayCharacter() const
{
    return '@';
}

void LockedDoorway::setCharacterAt(char direction)
{
}
