#ifndef WALL_H
#define WALL_H
#include <memory>
#include "roomedge.h"

namespace core {
namespace dungeon {
class Wall:public RoomEdge
{
public:
    Wall();
    virtual ~Wall(){}

    virtual std::string description() const override;
    virtual char displayCharacter() const override;
    virtual bool isPassage() const override;

    virtual void setCharacterAt(const char &direction) override=0;

};
}
}
#endif // WALL_H
