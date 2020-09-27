#include "weapon.h"
using namespace core::items;
Weapon::Weapon()
{

}
Weapon::Weapon(const std::string &name){
    itemName=name;
}

std::unique_ptr<Item> Weapon::clone() const {
    // does this really make a clone?
    return std::make_unique<Weapon>(*this);
}
