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

    int opposite; //not sure
    void connect(std::shared_ptr<Doorway> opposite); // not sure
    bool isEntrance();
    bool isExit();

    virtual std::string description() const override;
    virtual char displayCharacter() const override;
    virtual bool isPassage() const override;
};
}
}
#endif // DOORWAY_H
