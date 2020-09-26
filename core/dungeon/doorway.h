#ifndef DOORWAY_H
#define DOORWAY_H
#include <memory>
#include "roomedge.h"
#include <cstdlib>

namespace core {
namespace dungeon {

class Doorway: public RoomEdge
{
protected:
    Doorway* opposite; //not sure
    bool exit=false;
    bool entrance=false;
public:
    Doorway();
    virtual ~Doorway(){
        // TODO Doorway has no reason to delete another opposite doorway, it should be deleted by Doorway?
        opposite=nullptr;
        // Doorway itself will be deleted by room cz room has the ownership of shared_ptr doorway.
    };


    void connect(Doorway* opposite); // not sure
    bool isEntrance() const;
    bool isExit() const;
    virtual std::string description() const override;
    virtual char displayCharacter() const override;
    virtual bool isPassage() const override;

    virtual void setCharacterAt(char direction) override;
private:
    void disconnect(Doorway* doorway);
};
}
}
#endif // DOORWAY_H
