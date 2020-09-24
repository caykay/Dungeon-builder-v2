#include "doorway.h"
using namespace core::dungeon;
Doorway::Doorway()
{
    _entrance=false;
    _exit=false;
}
Doorway::Doorway(bool exit, bool entrance): _exit{exit}, _entrance{entrance}
{}


void Doorway::connect(Doorway* opposite){

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

bool Doorway::isEntrance()const{
    return _entrance;
}
bool Doorway::isExit()const {
    return _exit;
}


std::string Doorway::description() const{}

char Doorway::displayCharacter() const{
    //should they be implemented in sub classes?
    if(isExit()==true&&isEntrance()==false){
        return '0';
    }else if(isEntrance()==true&&isExit()==false){
        return 'I';
    }
}

bool Doorway::isPassage() const{
    if (isExit()||isEntrance()==true){
        return false;
    }
    return true;
}

void Doorway::disconnect(){
    this->opposite=nullptr;
}
