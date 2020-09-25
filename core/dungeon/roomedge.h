#ifndef ROOMEDGE_H
#define ROOMEDGE_H
#include <memory>


namespace core {
namespace dungeon {
class RoomEdge
{
protected:
    char character;
public:
    RoomEdge();
    virtual ~RoomEdge(){};


    virtual std::string description() const=0;
    virtual char displayCharacter() const=0;
    virtual bool isPassage() const=0;

    virtual void setCharacterAt( char direction)=0;
};
}
}
#endif // ROOMEDGE_H
