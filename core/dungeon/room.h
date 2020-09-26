#ifndef ROOM_H
#define ROOM_H
#include <memory>
#include <vector>
#include <map>
#include "core/dungeon/roomedge.h"
#include "core/items/item.h"
#include "core/creatures/abstractcreature.h"
// TODO check here
#include "core/dungeon/common/blockeddoorway.h"
#include "core/dungeon/common/lockeddoorway.h"
#include "core/dungeon/common/onewaydoor.h"
#include "core/dungeon/common/opendoorway.h"


namespace core {
namespace dungeon {
using OpenDoorWay=core::dungeon::common::OpenDoorWay;
using LockedDoorWay=core::dungeon::common::LockedDoorway;
using OneWayDoor=core::dungeon::common::OneWayDoor;
using BlockedDoorWay=core::dungeon::common::BlockedDoorway;

class Room
{
protected:
    int roomID;
    std::string getDirection(int pos) const;
public:
    Room();
    Room(int id);

    using RoomEdgePtr = std::shared_ptr<RoomEdge>;

    enum class Direction :unsigned int {North, South, East, West};
    virtual std::string description() const;

    void setEdge(RoomEdgePtr edge, Direction direction);
    RoomEdgePtr edgeAt(Direction direction) ;

    std::vector<std::string> display();
    int id();
    std::shared_ptr<core::items::Item> item() const;
    void setItem(std::shared_ptr<core::items::Item> newItem);
    std::shared_ptr<core::creatures::AbstractCreature> creature() const;
    void setCreature (std::shared_ptr<core::creatures::AbstractCreature> newCreature);
    std::map<Direction, RoomEdgePtr> edges;

    // TODO create doorways here
    // creates a new opendoorway with no parameters
    std::shared_ptr<OpenDoorWay> createOpenDoorway() const;
    // creates a new opendoorway with exit/entrance parameters
    std::shared_ptr<OpenDoorWay> createOpenDoorway(char type) const;
    // creates a new Locked doorway
    std::shared_ptr<LockedDoorWay> createLockedDoorway() const;
    // creates new Oneway Door
    std::shared_ptr<OneWayDoor> createOnewaydoor() const;
    // creates new Blocked Doorwat
    std::shared_ptr<BlockedDoorWay> createBlockedDoorway() const;

private:   
    std::shared_ptr<core::items::Item> _item;
    std::shared_ptr<core::creatures::AbstractCreature> _creature;
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
