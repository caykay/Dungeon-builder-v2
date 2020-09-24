#include "game.h"
using namespace core;

double Game::randomDouble() {
  return _realDistribution(_randomGenerator);
}

void Game::setDungeonType(std::shared_ptr<DungeonLevelBuilder> builder){

}
void Game::createExampleLevel(){}
void Game::createRandomLevel(const std::string &name, int width, int height){

}

void Game::displayLevel(const std::ostream &display){

}

std::unique_ptr<Game> Game::_theInstance;

Game &Game::instance(){
    if (!_theInstance){
        _theInstance .reset(new Game());
    }

    return *_theInstance;

}
