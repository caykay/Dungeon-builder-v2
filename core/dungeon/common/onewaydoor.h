#ifndef OPENWAYDOOR_H
#define OPENWAYDOOR_H
#include "core/dungeon/doorway.h"
namespace core {
namespace dungeon {
namespace common{


class OneWayDoor: public Doorway
{
public:
    OneWayDoor();

    std::string description() const override;
    char displayCharacter() const override;
    bool isPassage() const override;
    void setCharacterAt(char direction) override;

private:

};
}
}
}
#endif // OPENWAYDOOR_H
