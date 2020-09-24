#include "room.h"
#include "doorway.h"
using namespace core::dungeon;
// variable to represent shared_ptr type for RoomEdge class
using RoomEdgePtr=std::shared_ptr<RoomEdge>;
Room::Room()
{

}

Room::Room(int id): dungeonID{id} {

}

int Room::id(){
    return dungeonID;
}

void Room::setEdge(RoomEdgePtr edge, Direction direction){
    switch (direction) {
    case Direction::North:
        edge->setCharacterAt('n');
        break;
    case Direction::South:
        edge->setCharacterAt('s');
        break;
    case Direction::East:
        edge->setCharacterAt('e');
        break;
    case Direction::West:
        edge->setCharacterAt('w');
        break;
    edges[direction]= edge;
}
}

RoomEdgePtr Room::edgeAt(Direction direction){
    return edges[direction];
}

void Room::setItem(std::shared_ptr<core::items::Item> newItem){
    _item=newItem;
}

std::shared_ptr<core::items::Item> Room::item(){
    return _item;
}

std::shared_ptr<core::creatures::AbstractCreature> Room::creature(){
    return _creature;
}

void Room::setCreature (std::shared_ptr<core::creatures::AbstractCreature> newCreature){
    _creature=newCreature;
}


std::vector<std::string> Room::display(){
    std::vector<std::string> edgeV(5);

    edgeV.at(0)=firstLastRow(edges[Direction::North]->displayCharacter());
    edgeV.at(1)=emptyRow();
    edgeV.at(2)=midRow(edges[Direction::East]->displayCharacter()
            ,edges[Direction::West]->displayCharacter());
    edgeV.at(3)=emptyRow();
    edgeV.at(4)=firstLastRow(edges[Direction::South]->displayCharacter());

    return edgeV;
}

std::string Room::firstLastRow(char character){
    std::string row;
    int size=11;
    for (int i=0; i<size; i++){
        if (i==0){
            row+="+";
        }else if(i==size-1){
            row+="+";
        }else if(i==5){
            row+=character;
        }else{
            row+="-";
        }
    }
    return row;
}
std::string Room::midRow(char charAtEast, char charAtWest){
    std::string row;
    int size=11;
    for (int i=0; i<size; i++){
        if (i==0){
            row+=charAtWest;
        }else if(i==size-1){
            row+=charAtEast;
        }else if(i==4){
            row+=creatureChar();
        }else if(i==5){
            if(roomHasExit()==true){
                row+="*";
            }else{
                row+=" ";
            }
        }else if(i==6){
            row+=itemChar();
        }else{
            row+=" ";
        }
    }
    return row;
}
std::string Room::emptyRow(){
    std::string row;
    int size=11;
    for (int i=0; i<size; i++){
        if (i==0){
            row+="|";
        }else if(i==size-1){
            row+="|";
        }else{
            row+=" ";
        }
    }
    return row;
}

char Room::creatureChar(){
    if(!(_creature==nullptr)){
        return _creature->displayCharacter();
    }    else{
        return ' ';
    }

}

char Room::itemChar(){
    if(!(_item==nullptr)){
        return _item->displayCharacter();
    }else{
        return ' ';
    }
}

bool Room::roomHasExit(){
    return _roomExit;
}


void Room::checkHasExit(){
    for (int i=static_cast<int>(Direction::North); i <static_cast<int>(Direction::West); i++){
        // Checks if the room edge is a doorway
        if(!(std::dynamic_pointer_cast<Doorway>(edges.at(static_cast<Direction>(i)))==nullptr)){
            // Checks if the doorway is an exit door
            if (std::dynamic_pointer_cast<Doorway>(edges.at(static_cast<Direction>(i)))->isExit()){
                // sets the room has exit to true;
                _roomExit=true;
                break;
            }
        }
    }

}
