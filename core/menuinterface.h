#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H
#include <iostream>
#include "game.h"

namespace core {
class MenuInterface
{
public:
    MenuInterface();
    MenuInterface(std::ostream &display, std::istream &input);

    void displayWelcome(const std::string &author, const std::string &title) const;

    void run();
};
}//end core


#endif // MENUINTERFACE_H
