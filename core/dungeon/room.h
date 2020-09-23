#ifndef ROOM_H
#define ROOM_H
#include <memory>
#include <vector>
#include <map>
#include "core/dungeon/roomedge.h"
#include "core/items/item.h"
#include "core/creatures/abstractcreature.h"



namespace core {
namespace dungeon {

class RoomEdge;

class Room
{
public:
    Room();
    Room(int id);
    enum class Direction :unsigned {North, South, East, West};

    virtual std::string description() const=0;

    void setEdge(std::shared_ptr<RoomEdge> edge, Direction direction);
    std::shared_ptr<RoomEdge> edgeAt(Direction direction) const;

    //to be removed not sure tho
//    void setNorth(const std::shared_ptr<RoomEdge> roomEdge);
//    void setEast(const std::shared_ptr<RoomEdge> roomEdge);
//    void setSouth(const std::shared_ptr<RoomEdge> roomEdge);
//    void setWest(const std::shared_ptr<RoomEdge> roomEdge);

//    const std::shared_ptr<RoomEdge> getNorth();
//    const std::shared_ptr<RoomEdge> getEast();
//    const std::shared_ptr<RoomEdge> getSouth();
//    const std::shared_ptr<RoomEdge> getWest();

    std::vector<std::string> display();//not yet figured out
    int id();
    std::shared_ptr<core::items::Item> item();
    void setItem(std::shared_ptr<core::items::Item> newItem);
    std::shared_ptr<core::creatures::AbstractCreature> creature();
    void setCreature (std::shared_ptr<core::creatures::AbstractCreature> newCreature);

private:
    int _id;
    std::shared_ptr<core::items::Item> _item;
    std::shared_ptr<core::creatures::AbstractCreature> _creature;
    std::shared_ptr<core::dungeon::RoomEdge> edges[4];


//    Direction _edge;




};
}
}
#endif // ROOM_H
