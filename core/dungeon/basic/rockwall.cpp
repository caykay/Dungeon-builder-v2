#include "rockwall.h"
using namespace core::dungeon::basic;
RockWall::RockWall()
{

}

std::string RockWall::description() const{}
char RockWall::displayCharacter() const{
    return character;
}
bool RockWall::isPassage() const{
    return false;
}

void RockWall::setCharacterAt(const char &direction) {
    switch (tolower(direction)) {
    case 'n'|'s':
        this->character='-';
        break;
    case 'e'|'w':
        this->character='|';
        break;

    }
    this->character=character;
}
