#ifndef OPENDOORWAY_H
#define OPENDOORWAY_H
#include "core/dungeon/doorway.h"
namespace core {
namespace dungeon {
namespace common{


class OpenDoorWay:public Doorway
{
public:
    OpenDoorWay();

    std::string description() const override;
    char displayCharacter() const override;
    bool isPassage() const override;

};
}
}
}
#endif // OPENDOORWAY_H
