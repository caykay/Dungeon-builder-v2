#include "../headers/consumeable.h"
using namespace core::items;
Consumeable::Consumeable()
{
}
Consumeable::Consumeable(const std::string &name)
{
    itemName = name;
}

std::unique_ptr<Item> Consumeable::clone() const
{
    return std::make_unique<Consumeable>(*this);
}
