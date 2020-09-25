#include "quartzchamber.h"
#include "rockwall.h"
#include <sstream>
using namespace core::dungeon::basic;
QuartzChamber::QuartzChamber()
{

}

QuartzChamber::QuartzChamber(int id){
    roomID=id;
    // TODO set room to have 4 rockwalls
    this->setEdge(std::make_shared<RockWall>(),Direction::East);
    this->setEdge(std::make_shared<RockWall>(),Direction::West);
    this->setEdge(std::make_shared<RockWall>(),Direction::North);
    this->setEdge(std::make_shared<RockWall>(),Direction::South);
}

std::string QuartzChamber::description() const{
    std::stringstream description;
    std::string nxt="\n";
    std::string intro="To the ";
    std::string outro=" to another Chamber";
    description<<"A chamber that glitters like a thousand stars in the torchlight. (Quartz Chamber)"<<nxt;
    int count=0;
    while(count<(int)this->edges.size()){
        if(std::dynamic_pointer_cast<Wall>(this->edges.at(static_cast<Direction>(count)))){
            description<<intro<<this->getDirection(count)<<this->edges.at(static_cast<Direction>(count))->description()<<nxt;
        }else{
            description<<intro<<this->getDirection(count)<<this->edges.at(static_cast<Direction>(count))->description()<<outro<<nxt;
        }
        count++;
    }
    if((this->item()!=nullptr)){
        description<<"There is a "<<this->item()->name()<<" to pick"<<nxt;
    }
    if((this->creature())!=nullptr){
        description<<"There is a "<<this->creature()->name()<<" to fight"<<nxt;
    }
    return description.str();
}
