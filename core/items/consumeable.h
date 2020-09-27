#ifndef CONSUMEABLE_H
#define CONSUMEABLE_H
#include "item.h"

namespace  core{
namespace  items{
/**
 * @class Consumeable
 * @brief The Consumeable class. A specific type of
 * item that can be picked up in a room in a dungeon
 * and used to boost or assist the navigator. Inherits Item
 * class
 *
 * @author Cassian Kahema
 */
class Consumeable: public Item
{
public:
    /**
     * @brief Consumeable Default constructor
     */
    Consumeable();
    Consumeable(const std::string &name);
    /**
     * @brief clone An overriden function from class Item
     * @return
     */
    std::unique_ptr<Item> clone() const override;
};
}
}
#endif // CONSUMEABLE_H
