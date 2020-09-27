#ifndef LOCKEDDOORWAY_H
#define LOCKEDDOORWAY_H
#include "core/dungeon/doorway.h"
namespace core {
namespace dungeon {
namespace common{

/**
 * @class LockedDoorway
 * @brief The LockedDoorway class. Derived class from
 * Doorway, Its basically a Door that is locked
 */
class LockedDoorway: public Doorway
{
public:
    /**
     * @brief LockedDoorway Default constructor
     */
    LockedDoorway();

    std::string description() const override;
    char displayCharacter() const override;
    bool isPassage() const override;
    void setCharacterAt(char direction) override;

private:

};
}
}
}
#endif // LOCKEDDOORWAY_H
