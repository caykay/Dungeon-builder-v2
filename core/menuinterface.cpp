#include "menuinterface.h"

using namespace core;

MenuInterface::MenuInterface(std::ostream &display, std::istream &input)
    :_display{display}, _input{input}{

}

void MenuInterface::displayWelcome(const std::string &author, const std::string &title) const{
    std::cout<< "Welcome to: " <<title <<"\n";
    std::cout<< "                Developed by " <<author<<std::endl;
    std::cout<< "           COMP 3023 Software Development with C++"<<std::endl;

}


void MenuInterface::run(){
    emptyLinePrompt();
    displayMainMenu();
}



void MenuInterface::displayMainMenu() {
    _display<<"\nWhat would you like to do?"<<std::endl;
    _display<<"(g)enerate the example level"<<std::endl;
    _display<<"(r)andom dungeon level"<<std::endl;
    _display<<"(q)uit"<<std::endl;

    validifyMainMenuInput(getUserInput());
}

void MenuInterface::displayDNGDescribeMenu(){
    _display<<"What would you like to do?"<<std::endl;
    _display<<"(d)escribe the dungeon level"<<std::endl;
    _display<<"(v)iew the dungeon level"<<std::endl;
    _display<<"(r)eturn to the main menu"<<std::endl;

    switch(tolower(getUserInput())){
    case('d'):
        describeLvl();
        setCustomMenu(DNG_Exploration);
        break;
    case('v'):
        displayLvl();
        emptyLinePrompt();
        displayDNGDescribeMenu();
        break;
    case('r'):
        displayMainMenu();
        break;
    default:
        displayInvalidInputMessage();
        displayDNGDescribeMenu(); // recursive method
    }
}

void MenuInterface::displayDNGExplorationMenu(){
    _display<<"What would you like to do?"<<std::endl;
    _display<<"(d)escribe a room"<<std::endl;
    _display<<"(r)eturn to previous menu"<<std::endl;


    _input.clear();

    switch(tolower(getUserInput())){
    case('d'):
        describeRoom();
        emptyLinePrompt();
        displayDNGExplorationMenu();
        break;
    case('r'):
        displayDNGDescribeMenu();
        break;
    default:
        displayInvalidInputMessage();
        displayDNGExplorationMenu(); // recursive method
    }

}

char MenuInterface::getUserInput() const{
    char userInput;
    _input.clear();
    _input>>userInput;

    return userInput;
}

void MenuInterface::validifyMainMenuInput(char input) {

    switch(tolower(input)){
    case('g'):
        generateExampleLvl();
        setCustomMenu(DNG_DescribeView);

        break;
    case('r'):
        generateRandomLvl();
        setCustomMenu(DNG_DescribeView);
        break;
    case('q'):
        if (quitInterface()){
            _display<<"\n\nGoodbye !"<<std::endl;
            emptyLinePrompt();
        }else {
            displayMainMenu();
        }
        break;
    default:
        displayInvalidInputMessage();
        displayMainMenu();

 }
}



void MenuInterface::displayInvalidInputMessage() const{
    _display<<"Invalid Input please try again"<<std::endl;
}

bool MenuInterface::quitInterface() const{
    char userInput;
    _display<<"\n*Are you sure you want to quit? (y/n) *"<<std::endl;
    _input.clear();
    _input>>userInput;

    while (tolower(userInput)!='y'||tolower(userInput)!='y'){
        switch (tolower(userInput)) {
        case 'y':
            return true;
            break;
        case 'n':
            return false;
            break;
        default:
            displayInvalidInputMessage();
            _display<<"y/n?"<<std::endl;
            _input>>userInput;
        }
    }

    return true;
}

void MenuInterface::setCustomMenu(Menu menu){
    _customMenu=menu;

    switch (menu) {
    case DNG_DescribeView:
        displayDNGDescribeMenu();
        break;
    case DNG_Exploration:
        displayDNGExplorationMenu();
        break;

    }
}


void MenuInterface::generateExampleLvl(){
    _display<<"Creating Example Dungeon Level..."<<std::endl;

    _display<<"Dungeon Level created"<<std::endl;
}

void MenuInterface::generateRandomLvl(){

}

void MenuInterface::displayLvl()
{

}

void MenuInterface::describeLvl(){

}

void MenuInterface::describeRoom()
{

}


void MenuInterface::emptyLinePrompt(){
    std::string inputPlaceholder;
    _display<<"\n"<<std::endl;
    _display<<"*Press Enter to continue*\n";
    _input.ignore();
//    _input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}



