#include "doorway.h"
using namespace core::dungeon;
Doorway::Doorway()
{
}


void Doorway::connect(Doorway* newOpposite){
    // first disconnect this door (as well as the other door's opposite which is this door)
    // from its current door
    disconnect(this);

    if(newOpposite!=nullptr){
        //disconnect the opposite door from any of its connections
        disconnect(newOpposite);
        // connects current door to the passed in door parameter
        this->opposite=newOpposite;
        // connects the opposite door to this door respectively
        newOpposite->opposite=this;
    }
}
void Doorway::setCharacterAt(char direction){}
bool Doorway::isEntrance()const{
    return entrance;
}
bool Doorway::isExit()const {
    return exit;
}


std::string Doorway::description() const{}

char Doorway::displayCharacter() const{
    //should they be implemented in sub classes?
}

bool Doorway::isPassage() const{
}

void Doorway::disconnect(Doorway* otherDoorway){
    // if doorway is already connected then disconnect otherwise nothing to disconnect
    if (otherDoorway->isPassage()==true){
//       opposite->opposite=nullptr;
       otherDoorway->opposite=nullptr;
    }
}
