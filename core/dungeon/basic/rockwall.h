#ifndef ROCKWALL_H
#define ROCKWALL_H
#include "core/dungeon/wall.h"

namespace core {
namespace dungeon {
namespace magical{



class RockWall: public Wall
{
public:
    RockWall();

    std::string description() const override;
    char displayCharacter() const override;
    bool isPassage() const override;

};
}
}
}
#endif // ROCKWALL_H
