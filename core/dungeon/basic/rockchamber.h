#ifndef ROCKCHAMBER_H
#define ROCKCHAMBER_H
#include "core/dungeon/room.h"

namespace core {
namespace dungeon {
namespace basic{


class RockChamber:public Room
{
public:
    RockChamber();
    RockChamber(int id);

    std::string description() const override;
};
}
}
}
#endif // ROCKCHAMBER_H
