#ifndef ROOMEDGE_H
#define ROOMEDGE_H
#include <memory>


namespace core {
namespace dungeon {
/**
 * @class RoomEdge
 * @brief The RoomEdge class. Abstract representation of an object
 * present at the side of a room. It defines getters and setters
 * for important properties that a room egde may posses
 *
 * @author Cassian Kahema
 */
class RoomEdge
{
protected:
    /**
     * @brief character Character representation of the roomEdge
     */
    char character;
public:
    /**
     * @brief RoomEdge Default Constructor
     */
    RoomEdge();
    /**
     * @brief ~RoomEdge Virtual destructor
     */
    virtual ~RoomEdge(){};

    /**
     * @brief description Provides the description of the
     * type of room edge
     * @return String description of the room properties
     */
    virtual std::string description() const=0;
    /**
     * @brief displayCharacter Displays the character representation
     * of the room edge
     * @return character representing edge
     */
    virtual char displayCharacter() const=0;
    /**
     * @brief isPassage Returns a boolean state of whether the room edge
     * is a valid passage leading to another room
     * @return True if room is passage, False otherwise
     */
    virtual bool isPassage() const=0;
    /**
     * @brief setCharacterAt In special cases where a room edge has
     * may be represented by a different character depending on its
     * direction in the room, then this method is used to identify the
     * location where the room edge will be set.
     * 'n' for North
     * 's' for South
     * 'e' for East and
     * 'w' for West
     * @param direction character representing the direction of the roomedge
     */
    virtual void setCharacterAt( char direction)=0;
};
}
}
#endif // ROOMEDGE_H
