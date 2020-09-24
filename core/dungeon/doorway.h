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
public:
    Doorway();
    Doorway(bool exit, bool entrance);
    virtual ~Doorway(){
        delete this;
    };


    void connect(Doorway* opposite); // not sure
    bool isEntrance() const;
    bool isExit() const;
    virtual std::string description() const override;
    virtual char displayCharacter() const override;
    virtual bool isPassage() const override;

    virtual void setCharacterAt(const char &direction) override=0;
private:
    bool _exit;
    bool _entrance;
    void disconnect();
};
}
}
#endif // DOORWAY_H
