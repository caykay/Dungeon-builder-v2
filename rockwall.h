#ifndef ROCKWALL_H
#define ROCKWALL_H
#include "wall.h"

namespace core {
namespace dungeon {
namespace basic{


/**
 * @class RockWall
 * @brief The RockWall class. A derived type of wall.
 *
 * @author Cassian Kahema
 */
class RockWall: public Wall
{
public:
    /**
     * @brief RockWall Default constructor
     */
    RockWall();

    std::string description() const override;
    char displayCharacter() const override;
    bool isPassage() const override;
    void setCharacterAt(char direction) override;
};
}
}
}
#endif // ROCKWALL_H
