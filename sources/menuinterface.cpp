#include "../headers/menuinterface.h"
#include <sstream>

using namespace core;

MenuInterface::MenuInterface(std::ostream &display, std::istream &input)
    : _display{display}, _input{input}
{
}

void MenuInterface::displayWelcome(const std::string &author, const std::string &title) const
{
    _display << "Welcome to: " << title << "\n";
    _display << "                Developed by " << author << std::endl;
    _display << "           COMP 3023 Software Development with C++" << std::endl;
}

void MenuInterface::run()
{
    emptyLinePrompt();
    displayMainMenu();
}

void MenuInterface::displayMainMenu()
{
    _display << "\nWhat would you like to do?" << std::endl;
    _display << "(g)enerate the example level" << std::endl;
    _display << "(r)andom dungeon level" << std::endl;
    _display << "(q)uit" << std::endl;
    // gets character input and validifies it according to the main menu options
    validifyMainMenuInput(getCharInput());
}

void MenuInterface::displayDNGDescribeMenu()
{
    _display << "\nWhat would you like to do?" << std::endl;
    _display << "(d)escribe the dungeon level" << std::endl;
    _display << "(v)iew the dungeon level" << std::endl;
    _display << "(r)eturn to the main menu" << std::endl;

    switch (tolower(getCharInput()))
    {
    case ('d'):
        describeLvl();
        setCustomMenu(Menu::DNG_Exploration);
        break;
    case ('v'):
        displayLvl();
        emptyLinePrompt();
        displayDNGDescribeMenu();
        break;
    case ('r'):
        displayMainMenu();
        break;
    default:
        displayInvalidInputMessage();
        displayDNGDescribeMenu(); // recursive method to repeat until correct character is entered
    }
}

void MenuInterface::displayDNGExplorationMenu()
{
    _display << "\nWhat would you like to do?" << std::endl;
    _display << "(d)escribe a room" << std::endl;
    _display << "(r)eturn to previous menu" << std::endl;

    _input.clear();

    switch (tolower(getCharInput()))
    {
    case ('d'):
        describeRoom();
        emptyLinePrompt();
        displayDNGExplorationMenu(); // recursive method
        break;
    case ('r'):
        displayDNGDescribeMenu();
        break;
    default:
        displayInvalidInputMessage();
        displayDNGExplorationMenu(); // recursive method
    }
}

char MenuInterface::getCharInput() const
{
    char input;
    _input.clear();
    _input >> input;
    _input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

int MenuInterface::getIntInput() const
{
    int userInput;
    _input.clear();
    _input >> userInput;
    _input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (_input.fail())
    { // validates the input type is an int
        _input.clear();
        displayInvalidInputMessage();
        _input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        _input >> userInput;
        _input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return userInput;
}

std::string MenuInterface::getStringInput() const
{
    // TODO Get character input from console
    char userInput[100];
    _input.getline(userInput, 100);

    // validate input type is string
    while (_input.fail())
    {
        displayInvalidInputMessage();
        _input.getline(userInput, 100);
    }

    return userInput;
}

void MenuInterface::validifyMainMenuInput(char input)
{

    switch (tolower(input))
    {
    case ('g'):
        generateExampleLvl();
        setCustomMenu(Menu::DNG_DescribeView);

        break;
    case ('r'):
        generateRandomLvl();
        setCustomMenu(Menu::DNG_DescribeView);
        break;
    case ('q'):
        if (quitInterface())
        {
            _display << "\n\nGoodbye !" << std::endl;
            emptyLinePrompt();
        }
        else
        {
            displayMainMenu();
        }
        break;
    default:
        displayInvalidInputMessage();
        displayMainMenu();
    }
}

void MenuInterface::displayInvalidInputMessage() const
{
    _display << "Invalid Input please try again" << std::endl;
}

void MenuInterface::displayInvalidInputMessage(std::string message) const
{
    _display << message << std::endl;
}

bool MenuInterface::quitInterface() const
{
    char userInput;
    _display << "\n*Are you sure you want to quit? (y/n) *" << std::endl;
    _input.clear();
    _input >> userInput;

    while (tolower(userInput) != 'y' || tolower(userInput) != 'y')
    {
        switch (tolower(userInput))
        {
        case 'y':
            return true;
            break;
        case 'n':
            return false;
            break;
        default:
            displayInvalidInputMessage();
            _display << "y/n?" << std::endl;
            _input >> userInput;
        }
    }

    return true;
}

void MenuInterface::setCustomMenu(Menu menu)
{
    _customMenu = menu;

    switch (menu)
    {
    case Menu::DNG_DescribeView:
        displayDNGDescribeMenu();
        break;
    case Menu::DNG_Exploration:
        displayDNGExplorationMenu();
        break;
    }
}

void MenuInterface::generateExampleLvl()
{
    _display << "\nCreating Example Dungeon Level..." << std::endl;
    Game::instance().createExampleLevel();
    _display << "Dungeon Level created" << std::endl;
}

void MenuInterface::generateRandomLvl()
{
    std::string dngName;
    int rows;
    int cols;
    char lvl;

    _display << "\nWhat would you like to call the level?" << std::endl;
    dngName = getStringInput();
    while (dngName.empty() == true)
    {
        displayInvalidInputMessage("Please enter a valid name");
        dngName = getStringInput();
    }
    _display << "\nHow many rows in *" << dngName << "*?" << std::endl;
    rows = getIntInput();
    while (rows < 1 || rows > 4)
    {
        displayInvalidInputMessage("Please enter in range of 1 and 4");
        rows = getIntInput();
    }

    _display << "\nHow many columns in *" << dngName << "*?" << std::endl;
    cols = tolower(getIntInput());
    while (cols < 1 || cols > 4)
    {
        displayInvalidInputMessage("Please enter in range of 1 and 4");
        cols = getIntInput();
    }

    _display << "\nWhat type of dungeon level is it? (b)asic or (m)agical" << std::endl;
    lvl = tolower(getCharInput());
    while (!(lvl == 'b' || lvl == 'm'))
    {
        displayInvalidInputMessage();
        lvl = getCharInput();
    }

    _display << "\nCreating " << dngName << "..." << std::endl;

    Game::instance().setDungeonType('b');
    Game::instance().createRandomLevel(dngName, cols, rows);
    _display << "Dungeon Level created!" << std::endl;
}

void MenuInterface::displayLvl()
{
    // TODO view the dng level
    Game::instance().displayLevel(_display);
}

void MenuInterface::describeLvl()
{
    Game::instance().describeLevel(_display);
}

void MenuInterface::describeRoom()
{
    // TODO Describe Room
    int noOfRooms = Game::instance().level->numberOfRooms();
    std::stringstream range;
    range << "(1-" << noOfRooms << ")";
    int roomNo;
    _display << "\nWhich room would you like to describe?" << range.str() << std::endl;
    roomNo = getIntInput();
    while (roomNo < 1 || roomNo > noOfRooms)
    {
        _display << "Enter number between: " << range.str() << std::endl;
        _display << "Which room would you like to describe?" << range.str() << std::endl;
        roomNo = getIntInput();
    }
    Game::instance().describeRoom(_display, roomNo);
}

void MenuInterface::emptyLinePrompt()
{
    std::string inputPlaceholder;
    _display << "\n"
             << std::endl;
    _display << "*Press Enter to continue*\n";
    _input.ignore();
}
