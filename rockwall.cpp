#include "rockwall.h"
using namespace core::dungeon::basic;
RockWall::RockWall()
{

}

std::string RockWall::description() const{
    return "is a Rock wall";
}
char RockWall::displayCharacter() const{
    return character;
}
bool RockWall::isPassage() const{
    return false;
}

void RockWall::setCharacterAt(char direction) {
    switch (tolower(direction)) {
    case 'n':
    case 's':
        this->character='-';
        break;
    case 'e':
    case 'w':
        this->character='|';
        break;

    }
}
