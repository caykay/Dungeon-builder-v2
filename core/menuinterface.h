#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H
#include <iostream>
#include <vector>
#include "game.h"

namespace core {
/**
 * @class MenuInterface "menuinterface.h"
 * @brief The MenuInterface class
 * The MenuInterface class is responsible for monitoring and displaying
 * Menu options that a user will be presented to, and guide through the
 * dungeon building and view processes
 *
 * @author Cassian Kahema
 * @version 0.1
 */
class MenuInterface
{
public:
    /**
     * @brief Default constructor for MenuInterface
     */
    MenuInterface();
    /**
     * @brief Constructor that passes input and output stream parameters
     *
     * @param display - Output stream that displays program output on cons
     *        console
     * @param input - Input stream that accepts user input
     */
    MenuInterface(std::ostream &display, std::istream &input);
    /**
     * @brief displayWelcome Displays a welcome message
     * @param author The author name
     * @param title  The title of the application
     */
    void displayWelcome(const std::string &author, const std::string &title) const;
    /**
     * @brief run Executes the menu interface operations
     */
    void run();

private:
    // Stream that displays output
    std::ostream &_display;
    // Stream that reads input from console
    std::istream &_input;
    /**
     * @brief The Menu enum contains the sub menus after the main menu
     */
    enum class Menu {DNG_DescribeView, DNG_Exploration};
    // Menu enum object
    Menu _customMenu;

    /**
     * @brief displayMainMenu Display the first Main Menu
     *
     */
    void displayMainMenu();
    /**
     * @brief displayDNGDescribeMenu Display the first sub menu
     * of the interface and that is responsible for Describing a Dungeon
     */
    void displayDNGDescribeMenu();
    /**
     * @brief displayDNGExplorationMenu Display sub menu responsible for
     * Exploring a dungeon
     */
    void displayDNGExplorationMenu();
    /**
     * @brief setCustomMenu Sets a custom menu that has to be displayed
     * next
     *
     * @param menu Menu enum object that describes the menu type
     */
    void setCustomMenu(Menu menu) ;
    /**
     * @brief getCharInput Reads a character input from console
     * @return a single character from user.
     */
    char getCharInput() const;
    /**
     * @brief getStringInput Reads string input from console
     * @return String input from user
     */
    std::string getStringInput() const;
    /**
     * @brief getIntInput Reads integer input from console
     * @return Returns an integer
     */
    int getIntInput() const;
    /**
     * @brief validifyMainMenuInput Checks character input read from console if valid
     * towards the main menu.
     * @param input Character read from console
     */
    void validifyMainMenuInput(char input) ;
    /**
     * @brief displayInvalidInputMessage Displays a default "invalid input" prompt
     * when incorrect input is read.
     */
    void displayInvalidInputMessage() const;
    /**
     * @brief displayInvalidInputMessage Sets and displays a custom message prompt
     * for incorrect input read.
     * @param message Custom message to be displayed
     */
    void displayInvalidInputMessage(std::string message) const;
    /**
     * @brief quitInterface A prompt to confirm user when attempting to quit the application
     * @return a boolean value True if user wants to quick and False otherwise
     */
    bool quitInterface() const;
    /**
     * @brief emptyLinePrompt Prints an empty line onto console
     */
    void emptyLinePrompt();
    /**
     * @brief generateExampleLvl Generates an example Dungeon level set as default
     */
    void generateExampleLvl();
    /**
     * @brief generateRandomLvl Creates a new Dungeon level customizable by the user
     */
    void generateRandomLvl();
    /**
     * @brief displayLvl Displays on screen the structure of the just recent made Dungeon Level
     */
    void displayLvl();
    /**
     * @brief describeLvl Describes the contents and details of the current Dungeon Level
     */
    void describeLvl();
    /**
     * @brief describeRoom Describes a room in dungeon and its contents. Allows users to pick
     * any available room they wish to see description for
     */
    void describeRoom();
};// END MenuInterface
}//END core


#endif // MENUINTERFACE_H
