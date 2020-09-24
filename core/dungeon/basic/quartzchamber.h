#ifndef QUARTZCHAMBER_H
#define QUARTZCHAMBER_H
#include "core/dungeon/room.h"

namespace core {
namespace dungeon {
namespace basic{


class QuartzChamber:public Room
{
public:
    QuartzChamber();
    QuartzChamber(int id);

    std::string description() const override;
};
}
}
}
#endif // QUARTZCHAMBER_H
