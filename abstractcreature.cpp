#include "abstractcreature.h"

using namespace core::creatures;
AbstractCreature::AbstractCreature()
{

}

AbstractCreature::AbstractCreature(const std::string &name): creatureName{name}{

}

char AbstractCreature::displayCharacter(){
    return 'M';
}

std::string AbstractCreature::name(){
    return creatureName;
}
