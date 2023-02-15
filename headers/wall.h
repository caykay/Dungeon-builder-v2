#ifndef WALL_H
#define WALL_H
#include <memory>
#include <string>
#include "roomedge.h"

namespace core {
namespace dungeon {
/**
 * @class Wall
 * @brief The Wall class. This class is a specific type of a
 * room edge. Its a wall which means by default it has no
 * passage to another room to start with.
 *
 * @author Cassian Kahema
 */
class Wall:public RoomEdge
{
public:
    /**
     * @brief Wall Default Constructor
     */
    Wall();
    /**
     * @brief ~Wall Virtual Constructor
     */
    virtual ~Wall(){}

    virtual std::string description() const override;
    virtual char displayCharacter() const override;
    virtual bool isPassage() const override;

    virtual void setCharacterAt(char direction) override=0;

};
}
}
#endif // WALL_H
