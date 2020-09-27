#ifndef MAGICALDUNGEONLEVEL_H
#define MAGICALDUNGEONLEVEL_H
#include "dungeonlevel.h"
namespace core {
namespace dungeon {
namespace magical {

class MagicalDungeonLevel: public DungeonLevel
{
public:
    MagicalDungeonLevel();

    std::string description() const override;
};
}
}
}
#endif // MAGICALDUNGEONLEVEL_H
