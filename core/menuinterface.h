#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H
#include <iostream>
#include <vector>
#include "game.h"

namespace core {
class MenuInterface
{
public:
    MenuInterface();
    MenuInterface(std::ostream &display, std::istream &input);

    void displayWelcome(const std::string &author, const std::string &title) const;

    void run();

private:
    std::ostream &_display;
    std::istream &_input;

    enum Menu {DNG_DescribeView, DNG_Exploration};
    Menu _customMenu;


    void displayMainMenu();
    void displayDNGDescribeMenu();
    void displayDNGExplorationMenu();

    void setCustomMenu(Menu menu) ;

    char getCharInput() const;
    std::string getStringInput() const;
    int getIntInput() const;

    void validifyMainMenuInput(char input) ;




    void displayInvalidInputMessage() const;
    void displayInvalidInputMessage(std::string message) const;

    bool quitInterface() const;

    void emptyLinePrompt();

    void generateExampleLvl();
    void generateRandomLvl();
    void displayLvl();
    void describeLvl();
    void describeRoom();
};
}//end core


#endif // MENUINTERFACE_H
