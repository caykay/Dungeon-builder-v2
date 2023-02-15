#define AUTHOR "Cassian Kahema"
#define TITLE "Dungeon Builder"

#include <iostream>
#include "./headers/menuinterface.h"

using core::MenuInterface;

int main()
{

    MenuInterface menuinterface{std::cout, std::cin};

    menuinterface.displayWelcome(AUTHOR, TITLE);

    menuinterface.run();

    return 0;
}