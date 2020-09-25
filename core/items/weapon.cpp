#include "weapon.h"
using namespace core::items;
Weapon::Weapon()
{

}
Weapon::Weapon(const std::string &name){
    itemName=name;
}

Item *Weapon::clone() const {
    // does this really make a clone?
    return new Weapon(*this);
}
