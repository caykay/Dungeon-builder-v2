#ifndef DOORWAY_H
#define DOORWAY_H
#include <memory>
#include "roomedge.h"
namespace core {
namespace dungeon {

class Doorway: public RoomEdge
{
public:
    Doorway();
    virtual ~Doorway(){
        delete this;
    };

    Doorway* opposite; //not sure
    void connect(Doorway* opposite); // not sure
    bool isEntrance();
    bool isExit();

    virtual std::string description() const override;
    virtual char displayCharacter() const override;
    virtual bool isPassage() const override;

    void setOpposite(Doorway* opposite);
};
}
}
#endif // DOORWAY_H
