#ifndef MAGICWALL_H
#define MAGICWALL_H
#include "core/dungeon/wall.h"

namespace core {
namespace dungeon {
namespace magical{


class MagicWall : public Wall
{
public:
    MagicWall();
    std::string description() const override;
    char displayCharacter() const override;
    bool isPassage() const override;
    void setCharacterAt( char direction) override;
};
}
}
}
#endif // MAGICWALL_H
