#ifndef ROOMEDGE_H
#define ROOMEDGE_H
#include <memory>
#include "room.h"

namespace core {
namespace dungeon {
class RoomEdge
{
public:
    RoomEdge();

    std::unique_ptr<core::dungeon::Room> edges;
    virtual std::string description() const=0;
    virtual char displayCharacter() const=0;
    virtual bool isPassage() const=0;
};
}
}
#endif // ROOMEDGE_H
