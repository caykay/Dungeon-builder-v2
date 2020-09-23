#ifndef WEAPON_H
#define WEAPON_H
#include "item.h"
namespace  core{
namespace  items{

class Weapon: public Item
{
public:
    Weapon();
    Weapon(const std::string &name);

    std::unique_ptr<Item> clone() const override;
};
}
}
#endif // WEAPON_H
