#ifndef MONSTER_H
#define MONSTER_H
#include "abstractcreature.h"

namespace  core{
namespace  creatures{


/**
 * @class Monster
 * @brief The Monster class. Concrete creature
 * that may exist to haunt you in a dungeon room.
 *
 * @author Cassian Kahema
 */
class Monster: public AbstractCreature
{
public:
    /**
     * @brief Monster Default Constructor
     */
    Monster();
    /**
     * @brief Monster Constructor assigning name to monster
     * @param name Name of the monster
     */
    Monster(const std::string &name);

    std::unique_ptr<AbstractCreature> clone() const override;
private:

};
}
}
#endif // MONSTER_H
