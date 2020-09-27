#include "item.h"
using namespace core::items;
Item::Item()
{

}
Item::Item(const std::string &name): itemName(name){

}

char Item::displayCharacter(){
    return 'L';
}

std::unique_ptr<Item> Item::clone() const{

}

std::string Item::name(){
    return itemName;
}
