#include "consumeable.h"
using namespace core::items;
Consumeable::Consumeable()
{

}
Consumeable::Consumeable(const std::string &name){
    itemName=name;
}


Item *Consumeable::clone() const {
    return new Consumeable(*this);
}
