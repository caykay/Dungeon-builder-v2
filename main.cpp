/**
 * @mainpage DUNGEON LEVEL BUILDER
 *
 * This Application Gives a user access to creation of a form of dungeon simulation
 * where users playing would have to navigate their way in and out of the dungeon,
 * pick up random items they can use to boost up or heal, and weapons to fight.
 *
 * The First interface a user will interact with is the Menu Interface which provides
 * a brief walkthrough through Dungeon Level creations and Navigations.
 *
 * There are three menus involved with the Interface as follows:
 * i. The Main Menu which is the first to encounter when application is executed
 * ii. The Dungeon Description and View Menu
 * iii. The Dungeon Navigation. Exploration Menu.
 *
 * These Menus are created as loop events which allow users to navigate back to
 * previous menus or explore other menu options.
 *
 * Goodluck in you dungeon exploration.
 *
 * @author CASSIAN NYONGOLE KAHEMA
 */

#include <iostream>
#include "menuinterface.h"
#define AUTHOR "Cassian Kahema"
#define TITLE "Dungeon Builder"

using core::MenuInterface;
/**
 * @brief main Displays the welcome message and runs the MenuInterface
 * @return 0 if exit execution is successful
 */
int main(){
    MenuInterface menuInterface{std::cout, std::cin};

    menuInterface.displayWelcome(AUTHOR, TITLE);
    menuInterface.run();

    return 0;
}
