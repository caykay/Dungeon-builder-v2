#ifndef DOORWAY_H
#define DOORWAY_H
#include <memory>
#include "roomedge.h"
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
        // TODO switch back to delete and set nullptr when done debugging
        delete opposite;
        opposite=nullptr;
    };


    void connect(Doorway* opposite); // not sure
    bool isEntrance() const;
    bool isExit() const;
    virtual std::string description() const override;
    virtual char displayCharacter() const override;
    virtual bool isPassage() const override;

    virtual void setCharacterAt(char direction) override;
private:
    void disconnect();
};
}
}
#endif // DOORWAY_H
