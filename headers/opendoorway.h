#ifndef OPENDOORWAY_H
#define OPENDOORWAY_H
#include "doorway.h"
namespace core {
namespace dungeon {
namespace common{

/**
 * @class OpenDoorway
 * @brief The OpenDoorWay class. A derived class of
 * Doorway class. This class has two special cases.
 * One which it may be an entrance
 * another it may be an exit doorway.
 * In general form its a door that you can go through
 * in either rooms (origin and destination)
 *
 * @author Cassian Kahema
 */
class OpenDoorWay:public Doorway
{
public:
    /**
     * @brief OpenDoorWay Default Constructor
     */
    OpenDoorWay();
    /**
     * @brief OpenDoorWay Parameterized constructor, main purpose
     * is to identify if its an entrance room or exit.
     * if the passed in character is 'x' then the state
     * of the door is that of an exit, if character is
     * 'i' then state is an opendoorway.
     * @param state Character defining if entrance or exit
     */
    OpenDoorWay(char state);

    std::string description() const override;
    char displayCharacter() const override;
    bool isPassage() const override;
    void setCharacterAt(char direction) override;

private:

};
}
}
}
#endif // OPENDOORWAY_H
