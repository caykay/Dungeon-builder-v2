#ifndef ROCKCHAMBER_H
#define ROCKCHAMBER_H
#include "core/dungeon/room.h"

namespace core {
namespace dungeon {
namespace basic{

/**
 * @class RockChamber
 * @brief The RockChamber class. A specific type of room.
 * Most of its important implementation are in the Room base class.
 * This class is related to only basic type of dungeon levels
 *
 * @author Cassian Kahema
 */
class RockChamber:public Room
{
public:
    /**
     * @brief RockChamber Default constructor
     */
    RockChamber();
    /**
     * @brief RockChamber Creates a new room chamber with
     * id as its identifier
     * @param id identifier of rock chamer
     */
    RockChamber(int id);

    std::string description() const override;
};
}
}
}
#endif // ROCKCHAMBER_H
