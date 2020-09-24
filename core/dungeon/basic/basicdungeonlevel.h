#ifndef BASICDUNGEONLEVEL_H
#define BASICDUNGEONLEVEL_H
#include "core/dungeon/dungeonlevel.h"

namespace core{
namespace dungeon{
namespace basic{

class BasicDungeonLevel: public DungeonLevel
{
public:
    BasicDungeonLevel();
    BasicDungeonLevel(const std::string &name, int width, int height);
    std::string description() const override;
};
}
}
}
#endif // BASICDUNGEONLEVEL_H
