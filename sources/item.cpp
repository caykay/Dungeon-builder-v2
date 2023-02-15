#include "../headers/item.h"
using namespace core::items;
Item::Item()
{
}
Item::Item(const std::string &name) : itemName(name)
{
}

char Item::displayCharacter()
{
    return 'L';
}

std::string Item::name()
{
    return itemName;
}
