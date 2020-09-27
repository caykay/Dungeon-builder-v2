#ifndef QUARTZCHAMBER_H
#define QUARTZCHAMBER_H
#include "room.h"

namespace core {
namespace dungeon {
namespace basic{

/**
 * @class QuartzChamber
 * @brief The QuartzChamber class. A specific type of room.
 * Most of its important implementation are in the Room base class.
 * This class is related to only basic type of dungeon levels
 *
 * @author Cassian Kahema
 */
class QuartzChamber:public Room
{
public:
    /**
     * @brief QuartzChamber Default constructor
     */
    QuartzChamber();
    /**
     * @brief QuartzChamber Creates a new room chamber with
     * id as its identifier
     * @param id identifier of quartz chamer
     */
    QuartzChamber(int id);

    std::string description() const override;
};
}
}
}
#endif // QUARTZCHAMBER_H
