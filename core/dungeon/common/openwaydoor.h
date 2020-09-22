#ifndef OPENWAYDOOR_H
#define OPENWAYDOOR_H
#include "core/dungeon/doorway.h"
namespace core {
namespace dungeon {
namespace common{


class OpenWayDoor: public Doorway
{
public:
    OpenWayDoor();

    std::string description() const override;
    char displayCharacter() const override;
    bool isPassage() const override;

};
}
}
}
#endif // OPENWAYDOOR_H
