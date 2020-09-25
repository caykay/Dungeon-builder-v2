#include "basicdungeonlevel.h"
#include <sstream>
using namespace core::dungeon::basic;
BasicDungeonLevel::BasicDungeonLevel()
{

}
BasicDungeonLevel::BasicDungeonLevel(const std::string &name, int width, int height){
    levelName=name;
    levelWidth=width;
    levelHeight=height;
}

std::string BasicDungeonLevel::description() const{
    std::stringstream description;
    std::string nxt="\n";
    description<<this->name()<<nxt;
    description<<"Size: "<<this->width()<<" x "<<this->height()<<nxt;
    description<<"Type: "<<"Dark Cave(Basic Dungoen)";
    return description.str();
}

