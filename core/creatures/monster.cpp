#include "monster.h"
using namespace core::creatures;
Monster::Monster()
{

}

Monster::Monster(const std::string &name){
    creatureName=name;
}

 std::unique_ptr<AbstractCreature> Monster::clone()const{
    return std::make_unique<Monster>(new Monster(creatureName));
}
