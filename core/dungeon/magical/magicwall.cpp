#include "magicwall.h"
using namespace core::dungeon::magical;
MagicWall::MagicWall()
{

}

bool MagicWall::isPassage() const{
    return false;
}
std::string MagicWall::description() const{}
char MagicWall::displayCharacter() const{}

void MagicWall::setCharacterAt(const char &direction) {
    switch (tolower(direction)) {
    case 'n'|'s':
        this->character='-';
        break;
    case 'e'|'w':
        this->character='|';
        break;
    }

}
