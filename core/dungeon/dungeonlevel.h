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
protected:
    std::string levelName;
    int levelHeight;
    int levelWidth;
    std::map<int, std::shared_ptr<Room>> rooms;
public:
    DungeonLevel();
    DungeonLevel(const std::string &name, int width, int height);
    virtual ~DungeonLevel(){
//        delete this;
    }

    bool addRoom(std::shared_ptr<Room> room);
    std::shared_ptr<Room> retrieveRoom (int id);
    int width() const;
    int height() const;
    int numberOfRooms() const;
    std::string name() const;
    virtual std::string description() const=0;

    std::vector<std::string> display();

private:
    std::vector<std::string> getDungeonRows();
    int getLastID();

};
}
}
#endif // DUNGEONLEVEL_H
