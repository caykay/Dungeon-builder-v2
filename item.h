#ifndef ITEM_H
#define ITEM_H
#include <memory>
#include <string>

namespace  core{
namespace  items{
/**
 * @class Item
 * @brief The Item class.
 * This class implements the Prototype Design Pattern.
 * Its a representation of an item that can be picked
 * in a dungeon. It allows concrete prototypes to clone
 * themselves
 *
 * @author Cassian Kahema
 */
class Item
{
protected:
    /**
     * @brief itemName Name of the item
     */
    std::string itemName;
    /**
     * @brief character Character representation of the item
     */
    char character;

public:
    /**
     * @brief Item Default constructor
     */
    Item();
    /**
     * @brief Item Parametarized constructor that defines
     * a name of an idem
     * @param name Name of the item to be made
     */
    Item(const std::string &name);
    /**
     * @brief ~Item Virtual destructor
     *
     */
    virtual ~Item(){}
    /**
     * @brief clone Abstract function that when implemented
     * allows a concrete prototype object to clone itself
     * @return a cloned instance of a concrete Item
     */
    virtual std::unique_ptr<Item> clone() const=0;
    /**
     * @brief name Displays item name
     * @return Name of the item
     */
    std::string name();
    /**
     * @brief displayCharacter Displays character representing
     * an item
     * @return
     */
    char displayCharacter();

};
}
}


#endif // ITEM_H
