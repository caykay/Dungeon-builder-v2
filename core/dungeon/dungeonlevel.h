#ifndef DUNGEONLEVEL_H
#define DUNGEONLEVEL_H
#include <memory>
#include <vector>
#include <map>
#include "room.h"
namespace core {
namespace dungeon {

class DungeonLevel
{
public:
    DungeonLevel();
    DungeonLevel(const std::string &name, int width, int height);
    virtual ~DungeonLevel(){
        delete this;
    }

    bool addRoom(std::unique_ptr<Room> room);
    void retrieveRoom (int id);
    int width() const;
    int height() const;
    int numberOfRooms() const;
    std::string name() const;
    virtual std::string description() const=0;

    std::vector<std::string> display();

private:
    std::string _name;
    int _width;
    int _height;
    std::map<int, std::unique_ptr<Room>> rooms;

};
}
}
#endif // DUNGEONLEVEL_H
