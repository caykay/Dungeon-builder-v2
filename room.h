#ifndef ROOM_H
#define ROOM_H
#include <memory>
#include <vector>
#include <map>
#include "roomedge.h"
#include "item.h"
#include "abstractcreature.h"
#include "blockeddoorway.h"
#include "lockeddoorway.h"
#include "onewaydoor.h"
#include "opendoorway.h"


namespace core {
namespace dungeon {
using OpenDoorWay=core::dungeon::common::OpenDoorWay;
using LockedDoorWay=core::dungeon::common::LockedDoorway;
using OneWayDoor=core::dungeon::common::OneWayDoor;
using BlockedDoorWay=core::dungeon::common::BlockedDoorway;
/**
 * @class Room
 * @brief The Room class. This class describes properties a
 * room in a dungeon level. Each room has 4 corder/edges
 * These edges are marked as Directions: north, south, east
 * and west.
 *
 * @author Cassian Kahema
 */
using RoomEdgePtr = std::shared_ptr<RoomEdge>;
class Room
{
protected:
    /**
     * @brief roomID An integer that uniquely represent a room
     * in a dungeon level.
     */
    int roomID;
    /**
     * @brief getDirection Returns a name representation
     * of a direction according to the int that its represented
     * with in the Direction enum classs declared in this class.
     * This function is mainly used when returning a description
     * of room contents in the getDescription() function (check
     * Room types for its implementation)
     * @param pos Integer position which is to be converted to direction
     * @return Direction name
     */
    std::string getDirection(int pos) const;
public:
    /**
     * @brief Room Default Constructor
     */
    Room();
    /**
     * @brief Room Parameterized constructor that assigned a new
     * room with the assigned id as its identifier
     * @param id Integer identifier of a room
     */
    Room(int id);
    /**
     * @brief ~Room Virtual destructor
     */
    virtual ~Room(){}
    /**
     * @brief The Direction enum. A nested enumeration of Directions
     * that a room may have. The following are their integer equivalents
     * North=0
     * South=1
     * East=2
     * West=3
     */
    enum class Direction :unsigned int {North, South, East, West};
    /**
     * @brief description Provides a brief description of the room.
     * Its type contents(Item or monster) and Room edges.
     * @return String describing the room
     */
    virtual std::string description() const;
    /**
     * @brief setEdge Sets a specific type of RoomEdge at the side
     * of the room specified by the direction parameter.
     * @param edge RoomEdge to be set (Doorway or Wall)
     * @param direction Direction to place the RoomEdge
     */
    void setEdge(RoomEdgePtr edge, Direction direction);
    /**
     * @brief edgeAt Returns the edge present at the requested side
     * of the room
     * @param direction Side of the room
     * @return shared_ptr reference to a RoomEdge
     */
    RoomEdgePtr edgeAt(Direction direction) ;
    /**
     * @brief display Returns a vector of string that are the
     * visual representaion of the room and its contents
     * @return Vector of string
     */
    std::vector<std::string> display();
    /**
     * @brief id Retrieves the id of the room object
     * @return integer identifier of a room
     */
    int id();
    /**
     * @brief item Fetches the item present in the room
     * @return shared_ptr reference to item
     */
    std::shared_ptr<core::items::Item> item() const;
    /**
     * @brief setItem assigns an item object to the room
     * @param newItem Item to be added to the room
     */
    void setItem(std::shared_ptr<core::items::Item> newItem);
    /**
     * @brief creature Fetches the monster object present in the room
     * @return shared_ptr reference to the monster object
     */
    std::shared_ptr<core::creatures::AbstractCreature> creature() const;
    /**
     * @brief setCreature Assigned a creature object to a room
     * @param newCreature Creature to be added
     */
    void setCreature (std::shared_ptr<core::creatures::AbstractCreature> newCreature);
    /**
     * @brief edges This variable consits of RoomEdges references(shared_ptrs)
     * which are mapped to the room sides. Each per side.
     */
    std::map<Direction, RoomEdgePtr> edges;

    // TODO create doorways here
    /**
     * @brief createOpenDoorway creates a new opendoorway with no parameters
     * @return shared_ptr reference to opendoorway created
     */
    std::shared_ptr<OpenDoorWay> createOpenDoorway() const;
    /**
     * @brief createOpenDoorway creates a new opendoorway with exit/entrance parameters
     * @param type Character that defines the special case type of open
     * doorway. 'i' for entrance and 'x' for exit.
     * @return shared_ptr reference to opendoorway created
     */
    std::shared_ptr<OpenDoorWay> createOpenDoorway(char type) const;
    /**
     * @brief createLockedDoorway creates a new Locked doorway
     * @return shared_ptr reference to locked doorway created
     */
    std::shared_ptr<LockedDoorWay> createLockedDoorway() const;
    /**
     * @brief createOnewaydoor creates new Oneway Door
     * @return shared_ptr reference to one way door created
     */
    std::shared_ptr<OneWayDoor> createOnewaydoor() const;
    /**
     * @brief createBlockedDoorway creates new Blocked Doorway
     * @return shared_ptr reference to blocked doorway created
     */
    std::shared_ptr<BlockedDoorWay> createBlockedDoorway() const;
    /**
     * @brief roomHasExit True if room has an exit doorway and False otherwise
     * @return _roomExit
     */
    bool roomHasExit();
    /**
     * @brief hasEntrance True if room has an entrance doorway and False otherwise
     * @return _roomEntrance:
     */
    bool hasEntrance();

private:
    /**
     * @brief _item Item object present in room is stored here
     */
    std::shared_ptr<core::items::Item> _item;
    /**
     * @brief _creature Creature object present in room is stored here
     */
    std::shared_ptr<core::creatures::AbstractCreature> _creature;
    /**
     * @brief _roomExit Boolean value that states the situation
     * whether room has an exit doorway or not
     */
    bool _roomExit=false;
    /**
     * @brief _roomEntrance Boolean that states whether room has an entrance
     * or not
     */
    bool _roomEntrance=false;
    /**
     * @brief creatureChar Gets the character that represent the
     * current creature in the room only if there is one
     * @return character representation of a creature
     */
    char creatureChar();
    /**
     * @brief itemChar Gets the character that represents the
     * current item present in the room if there is one
     * @return character representation of an item
     */
    char itemChar();
    /**
     * @brief checkHasExit Checks if the room has an exit doorway
     */
    void checkHasExit();
    /**
     * @brief checkHasEntrance Checks if the room has an entrance doorway
     */
    void checkHasEntrance();

    //concatenators
    /**
     * @brief firstLastRow Concatenates the characters that represent the first
     * and last row of the rooms representation. Its then used later on
     * to construtct a final complete structure of the room. The passed in character
     * is a representation of the doorway/wall present North or South of the room
     * @param character Representation of North/South Room Edge
     * @return String representaion of the first/last row of rooms representation
     */
    std::string firstLastRow(char character);
    /**
     * @brief midRow Constructs the midrow of the general room representation
     * passes the character that represent the room edges at East/West of the room
     * @param charEast character representing the east doorway
     * @param charWest
     * @return  String representaion of the mid part of a room's representation
     */
    std::string midRow(char charEast, char charWest);
    /**
     * @brief emptyRow Creates a format of a constant row
     * in the rooms representation (between mid and top/bottom rows)
     * @return String representing an empty row in a room
     */
    std::string emptyRow();


};
}
}
#endif // ROOM_H
