#ifndef BASICDUNGEONLEVEL_H
#define BASICDUNGEONLEVEL_H
#include "dungeonlevel.h"

namespace core{
namespace dungeon{
namespace basic{
/**
 * @class BasicDungeonLevel
 * @brief The BasicDungeonLevel class. This is a more specific type
 * of a dungeon level class. Not much detail about it. Most of
 * implementations are in DungeonLevel class.
 *
 * @author Cassian Kahema
 */
class BasicDungeonLevel: public DungeonLevel
{
public:
    /**
     * @brief BasicDungeonLevel Default Constructor
     */
    BasicDungeonLevel();
    /**
     * @brief BasicDungeonLevel Parameterized constructor
     * that sets the details of the basic dungeon level
     * @param name Name of the basic dungeon
     * @param width Width of the dungeon level
     * @param height Height of the dungeon level
     */
    BasicDungeonLevel(const std::string &name, int width, int height);
    /**
     * @brief description Here is the implementation of the
     * specific descritption of a dungeon
     * Its name, and size
     * @return
     */
    std::string description() const override;
};
}
}
}
#endif // BASICDUNGEONLEVEL_H
