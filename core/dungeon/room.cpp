#include "room.h"
using namespace core::dungeon;
Room::Room()
{

}

Room::Room(int id): _id{id} {

}

int Room::id(){
    return _id;
}

void Room::setEdge(std::shared_ptr<RoomEdge> edge, Direction direction){
    edges[static_cast<int>(direction)]= std::make_shared<RoomEdge>(edge);
}

std::shared_ptr<RoomEdge> Room::edgeAt(Direction direction) const{
    return edges[static_cast<int>(direction)];
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

