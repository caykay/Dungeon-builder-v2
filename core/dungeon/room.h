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

class Room
{
protected:
    int dungeonID;
public:
    Room();
    Room(int id);

    using RoomEdgePtr = std::shared_ptr<RoomEdge>;

    enum class Direction :unsigned int {North, South, East, West};
    virtual std::string description() const=0;

    void setEdge(RoomEdgePtr edge, Direction direction);
    RoomEdgePtr edgeAt(Direction direction) ;

    std::vector<std::string> display();
    int id();
    std::shared_ptr<core::items::Item> item();
    void setItem(std::shared_ptr<core::items::Item> newItem);
    std::shared_ptr<core::creatures::AbstractCreature> creature();
    void setCreature (std::shared_ptr<core::creatures::AbstractCreature> newCreature);

private:   
    std::shared_ptr<core::items::Item> _item;
    std::shared_ptr<core::creatures::AbstractCreature> _creature;
    std::map<Direction, RoomEdgePtr> edges;
    bool _roomExit=false;

    char creatureChar();
    char itemChar();
    bool roomHasExit();
    void checkHasExit();

    //concatenators
    std::string firstLastRow(char character);
    std::string midRow(char charEast, char charWest);
    std::string emptyRow();
};
}
}
#endif // ROOM_H
