#include <iostream>
#include "core/menuinterface.h"
#define AUTHOR "Cassian Kahema"
#define TITLE "Dungeon Builder"

using core::MenuInterface;
int main(){
    MenuInterface menuInterface{std::cout, std::cin};

    menuInterface.displayWelcome(AUTHOR, TITLE);
    menuInterface.run();

}
