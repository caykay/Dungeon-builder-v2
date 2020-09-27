#ifndef BLOCKEDDOORWAY_H
#define BLOCKEDDOORWAY_H
#include "core/dungeon/doorway.h"
namespace core {
namespace dungeon {
namespace common{

/**
 * @class BlockedDoorway
 * @brief The BlockedDoorway class. A derived class from
 * Doorway class.  A blocked doorway is that that cant be
 * moved through in either sides of the room and opposite
 *
 * @author Cassian Kahema
 */
class BlockedDoorway : public Doorway
{
public:
    /**
     * @brief BlockedDoorway Default constructor
     */
    BlockedDoorway();

    std::string description() const override;
    char displayCharacter() const override;
    bool isPassage() const override;
    void setCharacterAt(char direction) override;

private:

};
}
}
}
#endif // BLOCKEDDOORWAY_H
