#ifndef BLOCKEDDOORWAY_H
#define BLOCKEDDOORWAY_H
#include "core/dungeon/doorway.h"
namespace core {
namespace dungeon {
namespace common{


class BlockedDoorway : public Doorway
{
public:
    BlockedDoorway();

    std::string description() const override;
    char displayCharacter() const override;
    bool isPassage() const override;
    void setCharacterAt(const char &direction) override;

private:

};
}
}
}
#endif // BLOCKEDDOORWAY_H
