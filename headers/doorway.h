#ifndef DOORWAY_H
#define DOORWAY_H
#include <memory>
#include <string>
#include "roomedge.h"
#include <cstdlib>

namespace core {
namespace dungeon {
/**
 * @class Doorway
 * @brief The Doorway class. This function specifies the content that may be present
 * on a roomedge. It inherits RoomEdge class. It specifies properties of a doorway
 * and defines interactions with other doorway specifically when one doorway connects
 * with another doorway of an opposite room. Or if a doorway is an exit or entrance
 * and more.
 *
 * @author Cassian Kahema
 */
class Doorway: public RoomEdge
{
protected:
    /**
     * @brief opposite Pointer reference to a Doorway connected
     * to the current doorway
     */
    Doorway* opposite;
    /**
     * @brief exit True when doorway is an exit
     * default set to false.
     */
    bool exit=false;
    /**
     * @brief entrance True when doorway us an entrance
     *
     */
    bool entrance=false;
public:
    /**
     * @brief Doorway Default constructor
     */
    Doorway();
    virtual ~Doorway(){
        // Get rid of dangling pointer opposite
        opposite=nullptr;
        // Doorway itself will be deleted by room cz room has the ownership of shared_ptr doorway.
    };

    /**
     * @brief connect Connects a doorway reference to the current doorway
     * by setting this opposite to the newOpposite also setting the other doorway's opposite
     * to this object
     * @param newOpposite Doorway object reference to be connected with
     */
    void connect(Doorway* newOpposite);
    /**
     * @brief isEntrance Defines whether a door is an entrance door
     * @return True if entrance, False otherwise
     */
    bool isEntrance() const;
    /**
     * @brief isExit Defines whether a doorway is an exit door
     * @return True if exit, False otherwise
     */
    bool isExit() const;
    // The following functions are described in RoomEdge class
    virtual std::string description() const override;
    virtual char displayCharacter() const override;
    virtual bool isPassage() const override;

    virtual void setCharacterAt(char direction) override;
private:
    /**
     * @brief disconnect Disconnects the passed in object to its current
     * opposite
     * @param otherDoorway Doorway that requires disconnection
     */
    void disconnect(Doorway* otherDoorway);
};
}
}
#endif // DOORWAY_H
