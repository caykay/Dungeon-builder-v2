#ifndef DUNGEONLEVEL_H
#define DUNGEONLEVEL_H
#include <memory>
#include <vector>
#include <map>
#include "room.h"
namespace core {
namespace dungeon {
/**
 * @class DungeonLevel
 * @brief The DungeonLevel class. This class specifies the characteristics
 * of a product created from a builder class and that is a dungone level.
 *
 * @author Cassian Kahema
 */
class DungeonLevel
{
protected:
    /**
     * @brief levelName Name of the dungeon level
     */
    std::string levelName;
    /**
     * @brief levelHeight Number of rows in dungeon
     */
    int levelHeight;
    /**
     * @brief levelWidth Number of columns in dungeon
     */
    int levelWidth;
    /**
     * @brief rooms Every room in a dungeon is mapped
     * to its specific int iD in this variable
     */
    std::map<int, std::shared_ptr<Room>> rooms;
public:
    /**
     * @brief DungeonLevel Default Constructor
     */
    DungeonLevel();
    /**
     * @brief ~DungeonLevel Virtual destructor
     */
    virtual ~DungeonLevel(){}
    /**
     * @brief DungeonLevel Parametarized constructor that assigns
     * name and size of the dungeon level
     * @param name Name of the dungeon level
     * @param width Width of the dungeon
     * @param height Height of the dungeon
     */
    DungeonLevel(const std::string &name, int width, int height);

    /**
     * @brief addRoom Adds a room to the current existing rooms in a dungeon.
     * Checks if the room can be added first before adding it.
     * @param room Room that is to be added in dungeon level
     * @return True if room was added successfully and false otherwise
     */
    bool addRoom(std::shared_ptr<Room> room);
    /**
     * @brief retrieveRoom Gets a room of a specified id if present
     * @param id Identifier of the dungeon
     * @return A shared_ptr reference to the room retrieved
     */
    std::shared_ptr<Room> retrieveRoom (int id);
    /**
     * @brief retrieveNearbyRoom Gets the neardby room
     * oppsite the room at the specified location in cases it
     * may return nullptr values, but for this scope it is likely
     * intended to return that for some checks to be perfomed on
     * some functions in Game class. For example if i want to know
     * whether there is a nearby room north i just check if the
     * function doesn't return nullptr, if it does then no room is there.
     * @param id ID of the current room
     * @param direction Direction to which we want to retrieve the opposite room
     * @return Shared_ptr reference of the nearby room
     */
    std::shared_ptr<Room> retrieveNearbyRoom (int id, Room::Direction direction);
    /**
     * @brief width Returns the width of the dungeon level
     * @return width of the dungeon level
     */
    int width() const;
    /**
     * @brief height Returns the height/(number of rows) of the dungeon
     * @return height of the dungeon level
     */
    int height() const;
    /**
     * @brief numberOfRooms Shows the number of current rooms in the dungeon
     * @return number of rooms
     */
    int numberOfRooms() const;
    /**
     * @brief name Shows the name of the dungeon level
     * @return Name of the dungeon level
     */
    std::string name() const;
    /**
     * @brief description Defines a specific destription of the dungeon
     * Name of the room and size and type of dungeon (basic or magical)
     * @return String representation of the dungeon level description
     */
    virtual std::string description() const=0;
    /**
     * @brief display Displays the complete structure of how rooms
     * are arranged in the dungeon as a vector of string. Also available
     * passages, items, monsters and Entrance of exit doorways.
     * @return String representation rows of the visual representation
     * of the dungeon level
     */
    std::vector<std::string> display();

    /**
     * @brief isLeftRoom Check if room aligned at left of the dungeon
     * Room can be left and corner at the same time but not right or mid.
     * @param id Id of room to be checked
     * @return True if room is at left false otherwise
     */
    bool isLeftRoom(int id);
    /**
     * @brief isRightRoom Check if room aligned at right of the dungeon
     * Room can be at right and corner at the same time but not left or mid.
     * @param id Id of room to be checked
     * @return
     */
    bool isRightRoom(int id);
    /**
     * @brief isTopRoom Check if room aligned at top of the dungeon
     * @param id Id of room to be checked
     * @return
     */
    bool isTopRoom(int id);
    /**
     * @brief isBottomRoom Check if room aligned at Bottom of the dungeon
     * @param id Id of room to be checked
     * @return
     */
    bool isBottomRoom(int id);
    /**
     * @brief isMidRoom Check if room is nether left or right aligned
     * and neither a corner room
     * @param id Id of room to be checked
     * @return
     */
    bool isMidRoom(int id);
    /**
     * @brief isCornerRoom Check if room aligned at the corners of the dungeon
     * @param id Id of room to be checked
     * @return
     */
    bool isCornerRoom(int id);
    /**
     * @brief isNonCornerRoom Check if room isn't aligned at corners
     * @param id Id of room to be checked
     * @return
     */
    bool isNonCornerRoom(int id);

private:
    /**
     * @brief getDungeonRows This function is delegated by the display()
     * function, its responsible to capture the representation of each
     * room in the dungeon and merge them together to form a complete
     * picture of the dungeon level
     * @return Vector os strings representing the structure of the dungeon
     * level
     */
    std::vector<std::string> getDungeonRows();
    /**
     * @brief getFirstRowIDs Captures the id of rooms alligned at
     * the top of dungeon
     * @return vector of room ids
     */
    std::vector<int> getFirstRowIDs();
    /**
     * @brief getLastRowIDs Captures the id of rooms aligned at the
     * last or bottom row
     * @return vector of room ids
     */
    std::vector<int> getLastRowIDs();
    /**
     * @brief getCornerRoomIds Captures the id of rooms aligned at the
     * corners of the dungeons
     * @return vector of room ids
     */
    std::vector<int> getCornerRoomIds();
    /**
     * @brief getNonCornerRoomIds Captures the id of rooms that are
     * not at the corners of the dungeons
     * @return vector of room ids
     */
    std::vector<int> getNonCornerRoomIds();
    /**
     * @brief getLeftRoomIds Captures the id of rooms aligned at the
     * left row of the dungeon level
     * @return vector of room ids
     */
    std::vector<int> getLeftRoomIds();
    /**
     * @brief getRightRoomIds Captures the id of rooms aligned at the
     * right row of the dungeon level
     * @return vector of room ids
     */
    std::vector<int> getRightRoomIds();
    /**
     * @brief getMidRoomIds Captures the id of rooms that are not
     * at the corners, not at the right or left of the dungeon level
     * @return vector of room ids
     */
    std::vector<int> getMidRoomIds();

    /**
     * @brief getLastID Retrieves the id of the last room
     * to be added in the dungeon level
     * @return Id of last room
     */
    int getLastID();

};
}
}
#endif // DUNGEONLEVEL_H
