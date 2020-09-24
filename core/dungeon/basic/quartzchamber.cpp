#include "quartzchamber.h"
using namespace core::dungeon::basic;
QuartzChamber::QuartzChamber()
{

}

QuartzChamber::QuartzChamber(int id){
    dungeonID=id;
}

std::string QuartzChamber::description() const{
    return "this is quartz chamber";
}
