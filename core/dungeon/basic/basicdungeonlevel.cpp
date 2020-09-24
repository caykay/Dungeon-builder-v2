#include "basicdungeonlevel.h"
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
    return "This is a basic dungeon level";
}
