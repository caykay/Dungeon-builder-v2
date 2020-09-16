#ifndef ROOM_H
#define ROOM_H
#include <memory>
#include "core/dungeon/roomedge.h"
#include "core/items/item.h"
#include "core/creatures/abstractcreature.h"



namespace core {
namespace dungeon {


class Room
{
public:
    Room();
    Room(int id);

    virtual std::string description() const=0;

    void setNorth(std::shared_ptr<Room> roomEdge);
    void setEast(std::shared_ptr<Room> roomEdge);
    void setSouth(std::shared_ptr<Room> roomEdge);
    void setWest(std::shared_ptr<Room> roomEdge);

    std::shared_ptr<core::dungeon::Room> getNorth();
    std::shared_ptr<Room> getEast();
    std::shared_ptr<Room> getSouth();
    std::shared_ptr<Room> getWest();

    std::string display();
    int id();
    core::items::Item item();
    void setItem(const core::items::Item &newItem);
    core::creatures::AbstractCreature creature();
    void setCreatusre (const core::creatures::AbstractCreature newCreature);

private:
    enum class Direction :unsigned {North, South, East, West};

    Direction _edge;
//    std::shared_ptr<RoomEdge> _edgeNorth;
//    std::shared_ptr<RoomEdge> _edgeEast;
//    std::shared_ptr<RoomEdge> _edgeSouth;
//    std::shared_ptr<RoomEdge> _edgeWest;
};
}
}
#endif // ROOM_H
