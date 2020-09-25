#ifndef ITEM_H
#define ITEM_H
#include <memory>

namespace  core{
namespace  items{

class Item
{
protected:
    std::string itemName;
    char character;

public:
    Item();
    Item(const std::string &name);
    virtual ~Item(){}

    virtual Item *clone() const;

    std::string name();
    char displayCharacter();

};
}
}


#endif // ITEM_H
