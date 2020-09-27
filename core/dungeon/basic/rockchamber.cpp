#include "rockchamber.h"
#include "rockwall.h"
#include <sstream>
using namespace core::dungeon::basic;
//using Doorway=core::dungeon::
RockChamber::RockChamber()
{

}
RockChamber::RockChamber(int id){
    roomID=id;
    // TODO set room to have 4 rockwalls
    this->setEdge(std::make_shared<RockWall>(),Direction::East);
    this->setEdge(std::make_shared<RockWall>(),Direction::West);
    this->setEdge(std::make_shared<RockWall>(),Direction::North);
    this->setEdge(std::make_shared<RockWall>(),Direction::South);

}

std::string RockChamber::description() const{
    std::stringstream description;
    // an empty line string
    std::string nxt="\n";
    // intro of a roomedge description
    std::string intro="To the ";
    // outro of doorway descritpion
    std::string outro=" to another Chamber";
    description<<"A chamber with hard rocky walls. (Rock Chamber)"<<nxt;
    int count=0;
    // Checks if the edges are walls or doorways and gets the correct description of them
    while(count<(int)this->edges.size()){
        if(std::dynamic_pointer_cast<Wall>(this->edges.at(static_cast<Direction>(count)))){
            description<<nxt<<intro<<this->getDirection(count)<<this->edges
                         .at(static_cast<Direction>(count))->description()<<nxt;
        }else{
            description<<nxt<<intro<<this->getDirection(count)<<this->edges
                         .at(static_cast<Direction>(count))->description()<<outro<<nxt;
        }
        count++;
    }
    // checks if the room has an item
    if((this->item()!=nullptr)){
        description<<"There is a "<<this->item()->name()<<" to pick"<<nxt;
    }
    // checks if the room has a creature
    if((this->creature())!=nullptr){
        description<<"There is a "<<this->creature()->name()<<" to fight"<<nxt;
    }
    return description.str();
}
