#ifndef LOCKEDDOORWAY_H
#define LOCKEDDOORWAY_H
#include "core/dungeon/doorway.h"
namespace core {
namespace dungeon {
namespace common{


class LockedDoorway: public Doorway
{
public:
    LockedDoorway();

    std::string description() const override;
    char displayCharacter() const override;
    bool isPassage() const override;

};
}
}
}
#endif // LOCKEDDOORWAY_H
