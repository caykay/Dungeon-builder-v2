#include "doorway.h"
using namespace core::dungeon;
Doorway::Doorway()
{

}


void Doorway::connect(Doorway* opposite){
    this->setOpposite(opposite);
    opposite->setOpposite(this);
}


void Doorway::setOpposite(Doorway* opposite){
    this->opposite=opposite;
}

std::string Doorway::description() const{}
char Doorway::displayCharacter() const{}
bool Doorway::isPassage() const{}
