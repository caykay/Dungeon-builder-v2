#include "rockchamber.h"
using namespace core::dungeon::basic;
RockChamber::RockChamber()
{

}
RockChamber::RockChamber(int id){
    dungeonID=id;
}

std::string RockChamber::description() const{
    return "This is a rock chamber";
}
