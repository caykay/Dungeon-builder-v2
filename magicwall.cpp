#include "magicwall.h"
using namespace core::dungeon::magical;
MagicWall::MagicWall()
{

}

bool MagicWall::isPassage() const{
    return false;
}
std::string MagicWall::description() const{
    return "is a Magic Wall";
}
char MagicWall::displayCharacter() const{}

void MagicWall::setCharacterAt(char direction) {
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
