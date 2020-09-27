#ifndef WEAPON_H
#define WEAPON_H
#include "item.h"
namespace  core{
namespace  items{
/**
 * @class Weapon
 * @brief The Weapon class. A concrete type that can be
 * used by a dungeon navigator to defend themselves.
 * Inherits class Item.
 * @author Cassian Kahema
 */
class Weapon: public Item
{
public:
    /**
     * @brief Weapon Default constructor
     */
    Weapon();
    Weapon(const std::string &name);
    /**
     * @brief clone An overriden function from class Item
     * @return
     */
    std::unique_ptr<Item> clone() const override;
};
}
}
#endif // WEAPON_H
