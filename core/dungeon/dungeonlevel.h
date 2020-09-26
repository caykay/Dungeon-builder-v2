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
    // gets the room nearby to that of the specified id
    std::shared_ptr<Room> retrieveNearbyRoom (int id, Room::Direction direction);
    int width() const;
    int height() const;
    int numberOfRooms() const;
    std::string name() const;
    virtual std::string description() const=0;

    std::vector<std::string> display();


    bool isLeftRoom(int id);
    bool isRightRoom(int id);
    bool isTopRoom(int id);
    bool isBottomRoom(int id);
    bool isMidRoom(int id);
    bool isCornerRoom(int id);
    bool isNonCornerRoom(int id);

private:
    std::vector<std::string> getDungeonRows();

    std::vector<int> getFirstRowIDs();
    std::vector<int> getLastRowIDs();
    std::vector<int> getCornerRoomIds();
    std::vector<int> getNonCornerRoomIds();
    std::vector<int> getLeftRoomIds();
    std::vector<int> getRightRoomIds();
    std::vector<int> getMidRoomIds();


    int getLastID();
    int getAboveRoomId(int id);
    int getBelowRoomId(int id);
    int getRightRoomId(int id);
    int getLeftRoomId(int id);

};
}
}
#endif // DUNGEONLEVEL_H
