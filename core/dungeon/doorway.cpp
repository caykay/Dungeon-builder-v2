#include "doorway.h"
using namespace core::dungeon;
Doorway::Doorway()
{
}


void Doorway::connect(Doorway* opposite){
    // first disconnect this door (as well as the other door's opposite which is this door)
    // from its current door
    disconnect(this);

    if(opposite!=nullptr){
        //disconnect the opposite door from any of its connections
        disconnect(opposite);
        // connects current door to the passed in door parameter
        this->opposite=opposite;
        // connects the opposite door to this door respectively
        opposite->opposite=this;
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

void Doorway::disconnect(Doorway* doorway){
    // if doorway is already connected then disconnect otherwise nothing to disconnect
    if (doorway->isPassage()==true){
//       opposite->opposite=nullptr;
       doorway->opposite=nullptr;
    }
}
