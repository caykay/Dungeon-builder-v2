#ifndef DOORWAY_H
#define DOORWAY_H
#include <memory>
namespace core {
namespace dungeon {

class Doorway
{
public:
    Doorway();

    int opposite; //not sure
    void connect(Doorway* &opposite); // not sure
    bool isEntrance();
    bool isExit();

    virtual std::string description() const=0;
    virtual char displayCharacter() const=0;
    virtual bool isPassage() const=0;
};
}
}
#endif // DOORWAY_H
