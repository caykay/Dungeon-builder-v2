#include "doorway.h"
using namespace core::dungeon;
Doorway::Doorway()
{
}


void Doorway::connect(Doorway* opposite){
    // first disconnect this door (as well as the other door's opposite which is this door)
    // from its current door
    this->disconnect();

    if(opposite!=nullptr){
        //disconnect the opposite door from any of its connections
        opposite->disconnect();
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
    if (isExit()||isEntrance()==true){
        return false;
    }
    if (opposite!=nullptr){
        // returns true if doorway is already connected
        return true;
    }
    return false;
}

void Doorway::disconnect(){
    // if doorway is already connected then disconnect otherwise nothing to disconnect
    if (isPassage()==true){
       opposite->opposite=nullptr;
       this->opposite=nullptr;
    }
}
