#ifndef OPENWAYDOOR_H
#define OPENWAYDOOR_H
#include "doorway.h"
namespace core {
namespace dungeon {
namespace common{

/**
 * @class OneWayDoor
 * @brief The OneWayDoor class . A derived class from
 * Doorway class. A oneway door is that that you can go through to
 * another room but cant get in back again from the same doorway.
 *
 * @author Cassian Kahema
 */
class OneWayDoor: public Doorway
{
public:
    /**
     * @brief OneWayDoor Default Constructor
     */
    OneWayDoor();

    std::string description() const override;
    char displayCharacter() const override;
    bool isPassage() const override;
    void setCharacterAt(char direction) override;

private:

};
}
}
}
#endif // OPENWAYDOOR_H
