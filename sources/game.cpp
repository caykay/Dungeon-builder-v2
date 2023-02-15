#include "../headers/game.h"
#include "../headers/basicdungeonlevelbuilder.h"
#include "../headers/room.h"
#include <algorithm>
#include "../headers/doorway.h"

using namespace core;
using BasicDLB = core::dungeon::basic::BasicDungeonLevelBuilder;
std::unique_ptr<Game> Game::_theInstance;

double Game::randomDouble()
{
    return _realDistribution(_randomGenerator);
}

void Game::setDungeonType(char type)
{
    switch (tolower(type))
    {
    case 'b':

        // set dungeon type to basicDungeon level builder
        setDungeonType(new BasicDLB());
        break;
    case 'm':
        // set dungeon type to magic dungeon level builder
        // Not implemented(optional)
        break;
    }
}

void Game::setDungeonType(DLB *builder)
{
    // clears the previous builder
    clearBuilder();
    this->builder = builder;
}
void Game::createExampleLevel()
{
    // clears the current level before building a new one
    clearLevel();
    setDungeonType(new BasicDLB());
    builder->buildDungeonLevel("Example Dungeon Level", 3, 3);
    level = builder->getDungeonLevel();

    createExampleRooms();
    buildExampleDoorways();
    buildExampleItems();
    buildExampleCreatures();
}
void Game::createRandomLevel(const std::string &name, int width, int height)
{
    // clears the current level before building a new one
    clearLevel();
    builder->buildDungeonLevel(name, width, height);
    level = builder->getDungeonLevel();
    addRandomRooms(width * height);
    buildRandomDoorways();
    addRandomCreatures();
    addRandomItems();
}

void Game::displayLevel(std::ostream &display)
{
    for (std::string row : level->display())
    {
        display << row << std::endl;
    }
}

void Game::describeLevel(std::ostream &display)
{
    display << level->description();
}

void Game::describeRoom(std::ostream &display, int id)
{
    Room room = level->retrieveRoom(id);
    display << room->description() << std::endl;
}

Game &Game::instance()
{
    if (!_theInstance)
    {
        _theInstance.reset(new Game());
    }

    return *_theInstance;
}

// deletes the raw pointer to level (reduce memory leak)
void Game::clearLevel()
{
    if (level != nullptr)
    {
        level = nullptr;
        delete level;
    }
}

void Game::clearBuilder()
{
    if (builder != nullptr)
    {
        builder = nullptr;
        delete builder;
    }
}

void Game::createExampleRooms()
{

    level->addRoom(builder->buildRoom(1));
    level->addRoom(builder->buildRoom(2));
    level->addRoom(builder->buildRoom(3));
    level->addRoom(builder->buildRoom(4));
    level->addRoom(builder->buildRoom(5));
    level->addRoom(builder->buildRoom(6));
    level->addRoom(builder->buildRoom(7));
    level->addRoom(builder->buildRoom(8));
    level->addRoom(builder->buildRoom(9));
}
void Game::buildExampleDoorways()
{
    builder->buildEntrance(level->retrieveRoom(1), Direction::North);
    builder->buildDoorway(level->retrieveRoom(1), level->retrieveRoom(2), Direction::East, MoveConstraints::None);
    builder->buildDoorway(level->retrieveRoom(1), level->retrieveRoom(4), Direction::South, MoveConstraints::DestinationImpassable);
    builder->buildDoorway(level->retrieveRoom(2), level->retrieveRoom(3), Direction::East, MoveConstraints::OriginImpassable | MoveConstraints::DestinationImpassable);
    builder->buildDoorway(level->retrieveRoom(2), level->retrieveRoom(5), Direction::South, MoveConstraints::None);
    builder->buildDoorway(level->retrieveRoom(3), level->retrieveRoom(6), Direction::South, MoveConstraints::DestinationLocked);
    builder->buildDoorway(level->retrieveRoom(4), level->retrieveRoom(5), Direction::East, MoveConstraints::DestinationImpassable);
    builder->buildDoorway(level->retrieveRoom(4), level->retrieveRoom(7), Direction::South, MoveConstraints::OriginImpassable | MoveConstraints::DestinationImpassable);
    builder->buildDoorway(level->retrieveRoom(5), level->retrieveRoom(8), Direction::South, MoveConstraints::None);
    builder->buildDoorway(level->retrieveRoom(5), level->retrieveRoom(6), Direction::East, MoveConstraints::None);
    builder->buildDoorway(level->retrieveRoom(7), level->retrieveRoom(8), Direction::East, MoveConstraints::OriginLocked | MoveConstraints::DestinationLocked);
    builder->buildDoorway(level->retrieveRoom(8), level->retrieveRoom(9), Direction::East, MoveConstraints::None);
    builder->buildExit(level->retrieveRoom(9), Direction::East);
}

void Game::buildExampleItems()
{
    builder->buildItem(level->retrieveRoom(3));
    builder->buildItem(level->retrieveRoom(5));
    builder->buildItem(level->retrieveRoom(7));
}

void Game::buildExampleCreatures()
{
    builder->buildCreature(level->retrieveRoom(3));
    builder->buildCreature(level->retrieveRoom(5));
    builder->buildCreature(level->retrieveRoom(9));
}

void Game::addRandomRooms(int size)
{
    // Loop through all intergers from 1 to size
    // sets them as room ids
    for (int i = 1; i <= size; i++)
    {
        level->addRoom(builder->buildRoom(i));
    }
}
/**
 *
 * NOTE THE FOLLOWING FUNCTION CHECKS FOR SPECIFIC 4 CASES
 * 1x1
 * 1xn
 * nx1
 * in some of these cases some function will return same results,
 * so only one of them will be modified to handle the cases and will then be called
 */
void Game::buildRandomDoorways()
{
    // Builds random entrance
    buildRandomEntrance();
    // Builds random exit
    buildRandomExit();

    if (level->width() == 1)
    {
        if (level->height() == 1)
        {
            // we do not build anything in a 1x1 case
        }
        else
        {
            // only build top and bottom
            // Build Corner rooms
            buildTopLeftCornerRoom(); // theres only one corner
            // these will be considered midrooms in this case
            buildLeftRooms();
            buildBottomLeftCornerRoom();
        }
    }
    else
    {
        // n x 1 case
        if (level->height() == 1)
        {
            // we only build top rows
            buildTopLeftCornerRoom();
            buildTopRightCornerRoom();
            buildTopRooms();
        }
        else
        {
            // this is the general nxn case
            // Build Corner rooms
            buildCornerRooms();
            // build Non Corner rooms
            buildNonCornerRooms();
        }
    }
}

void Game::buildCornerRooms()
{
    // a corner room only has two sides it can connect
    // and the constraint tells us a minimum of 1

    buildTopLeftCornerRoom();
    buildTopRightCornerRoom();
    buildBottomLeftCornerRoom();
    buildBottomRightCornerRoom();
}

// A non corner room has 5 cases
// i. room is top row but not corner
// ii. room is left row but not corner
// iii.room is right row but not corner
// iv. room is bottom row but not corner
// v. room is non of the above making it around mid row
void Game::buildNonCornerRooms()
{
    // Build top&bottom room doorways
    buildTopRooms();
    buildBottomRooms();
    // Build left&right room doorways
    buildLeftRooms();
    buildRightRooms();
    // Build mid room doorways
    buildMidRooms();
}

void Game::buildTopLeftCornerRoom()
{
    // Loop all through all rooms in level (by id)
    for (int id = 1; id <= level->numberOfRooms(); id++)
    {
        // check if rooom is corner room
        if (level->isCornerRoom(id) == true)
        {
            // check if room is in top row
            if (level->isTopRoom(id) == true)
            {
                // check if room is on the left side(so we know which direction we set our doorway)
                if (level->isLeftRoom(id))
                {
                    // Building the doorway
                    // since we dealing with 2 sides then get random number either 1(south) or 2 (east)
                    // since its a top left corner

                    // another check for cases where width=1
                    if (level->width() == 1)
                    {
                        if (level->height() == 1)
                        {
                            // no building doorways since there is only one room
                        }
                        else
                        {
                            // 1 x n case
                            // otherwise we can only connect with the room below
                            // check if connection exists
                            if ((level->retrieveRoom(id)->edgeAt(Direction::South)->isPassage()) == true)
                            {
                            }
                            else
                            {
                                builder->buildDoorway(level->retrieveRoom(id), level->retrieveNearbyRoom(id, Direction::South), Direction::South, getConstraint());
                            }
                            return; // function ends here
                        }
                    }
                    else
                    {
                        // also it may be a n x 1 case
                        if (level->height() == 1)
                        {
                            // can be connected to only right (east)
                            if ((level->retrieveRoom(id)->edgeAt(Direction::East)->isPassage()) == true)
                            {
                            }
                            else
                            {
                                builder->buildDoorway(level->retrieveRoom(id), level->retrieveNearbyRoom(id, Direction::East), Direction::East, getConstraint());
                            }
                            return; // function ends here
                        }
                    }
                    // Otherwise room has none of the above cases of 1x1, 1xn , nx1
                    Direction side = static_cast<Direction>(getRandomBtn(1, 2));
                    Direction otherSide = (side == Direction::East) ? Direction::South : Direction::East;
                    // get random number tht determine if we building
                    // minimum of 1 doorway or an extra doorway as well
                    int num = getRandomBtn(1, 2); // random to determine case

                    // This will always happen on any roll(satisfies the constraint)
                    if (num == 2 || num == 1)
                    {
                        buildRoomDoorway(id, side);
                    }
                    // the extra case
                    if (num == 1)
                    {
                        buildRoomDoorway(id, otherSide);
                    }
                }
            }
        }
    }
}

void Game::buildTopRightCornerRoom()
{
    // Loop all through all rooms in level (by id)
    for (int id = 1; id <= level->numberOfRooms(); id++)
    {
        // check if rooom is corner room
        if (level->isCornerRoom(id) == true)
        {
            // check if room is in top row
            if (level->isTopRoom(id) == true)
            {
                // check if room is on the right side(so we know which direction we set our doorway)
                if (level->isRightRoom(id))
                {
                    // Building the doorway

                    // another check for cases where width=1 and width=1
                    if (level->width() == 1)
                    {
                        if (level->height() == 1)
                        {
                            // no building doorways since there is only one room
                        }
                        else
                        {
                            // 1 x n case
                            // otherwise we can only connect with the room below
                            // check if connection exists
                            if ((level->retrieveRoom(id)->edgeAt(Direction::South)->isPassage()) == true)
                            {
                            }
                            else
                            {
                                builder->buildDoorway(level->retrieveRoom(id), level->retrieveNearbyRoom(id, Direction::South), Direction::South, getConstraint());
                            }
                            return; // function ends here
                        }
                    }
                    else
                    {
                        // also it may be a n x 1 case
                        if (level->height() == 1)
                        {
                            // can be connected to only left (west)
                            if ((level->retrieveRoom(id)->edgeAt(Direction::West)->isPassage()) == true)
                            {
                            }
                            else
                            {
                                builder->buildDoorway(level->retrieveRoom(id), level->retrieveNearbyRoom(id, Direction::West), Direction::West, getConstraint());
                            }
                            return; // function ends here
                        }
                    }
                    // since we dealing with 2 sides then get random number either 1(south) or 3 (west)
                    // since its a top left corner
                    Direction side = static_cast<Direction>(getRandomBtn(1, 3));
                    Direction otherSide = (side == Direction::West) ? Direction::South : Direction::West;
                    // get random number tht determine if we building
                    // minimum of 1 doorway or an extra doorway as well
                    int num = getRandomBtn(1, 2); // random to determine case

                    // This will always happen on any roll(satisfies the constraint)
                    if (num == 2 || num == 1)
                    {
                        buildRoomDoorway(id, side);
                    }
                    // the extra case
                    if (num == 1)
                    {
                        buildRoomDoorway(id, otherSide);
                    }
                }
            }
        }
    }
}

void Game::buildBottomLeftCornerRoom()
{
    // Loop all through all rooms in level (by id)
    for (int id = 1; id <= level->numberOfRooms(); id++)
    {
        // check if rooom is corner room
        if (level->isCornerRoom(id) == true)
        {
            // check if room is in bottom row
            if (level->isBottomRoom(id) == true)
            {
                // check if room is on the right side(so we know which direction we set our doorway)
                if (level->isLeftRoom(id))
                {
                    // Building the doorway
                    // another check for cases where width=1 or height=1
                    if (level->width() == 1)
                    {
                        if (level->height() == 1)
                        {
                            // no building doorways since there is only one room
                        }
                        else
                        {
                            // 1 x n case
                            // otherwise we can only connect with the room above
                            // check if connection exists
                            if ((level->retrieveRoom(id)->edgeAt(Direction::North)->isPassage()) == true)
                            {
                            }
                            else
                            {
                                builder->buildDoorway(level->retrieveRoom(id), level->retrieveNearbyRoom(id, Direction::North), Direction::North, getConstraint());
                            }
                            return; // function ends here
                        }
                    }
                    else
                    {
                        // for an n by 1 case this should not exist since there should not be a row below
                        if (level->height() == 1)
                        {
                            // Do nothing
                            return; // function ends here
                        }
                    }
                    // since we dealing with 2 sides then get random number either 0(north) or 2 (east)
                    // since its a top left corner
                    Direction side = static_cast<Direction>(getRandomBtn(0, 2));
                    Direction otherSide = (side == Direction::North) ? Direction::East : Direction::North;
                    // get random number tht determine if we building
                    // minimum of 1 doorway or an extra doorway as well
                    int num = getRandomBtn(1, 2); // random to determine case
                    // This will always happen on any roll(satisfies the constraint)
                    if (num == 2 || num == 1)
                    {
                        buildRoomDoorway(id, side);
                    }
                    // the extra case
                    if (num == 1)
                    {
                        buildRoomDoorway(id, otherSide);
                    }
                }
            }
        }
    }
}

void Game::buildBottomRightCornerRoom()
{
    // Loop all through all rooms in level (by id)
    for (int id = 1; id <= level->numberOfRooms(); id++)
    {
        // check if rooom is corner room
        if (level->isCornerRoom(id) == true)
        {
            // check if room is in bottom row
            if (level->isBottomRoom(id) == true)
            {
                // check if room is on the right side(so we know which direction we set our doorway)
                if (level->isRightRoom(id))
                {
                    // Building the doorway
                    // another check for cases where width=1 or height=1
                    if (level->width() == 1)
                    {
                        if (level->height() == 1)
                        {
                            // no building doorways since there is only one room
                        }
                        else
                        {
                            // 1 x n case
                            // otherwise we can only connect with the room above
                            // check if connection exists
                            if ((level->retrieveRoom(id)->edgeAt(Direction::North)->isPassage()) == true)
                            {
                            }
                            else
                            {
                                builder->buildDoorway(level->retrieveRoom(id), level->retrieveNearbyRoom(id, Direction::North), Direction::North, getConstraint());
                            }
                            return; // function ends here
                        }
                    }
                    else
                    {
                        // for an n by 1 case this should not exist since there should not be a row below
                        if (level->height() == 1)
                        {
                            // Do nothing
                            return; // function ends here
                        }
                    }

                    // since we dealing with 2 sides then get random number either 0(north) or 3 (west)
                    // since its a top left corner
                    Direction side = static_cast<Direction>(getRandomBtn(0, 3));
                    Direction otherSide = (side == Direction::West) ? Direction::North : Direction::West;
                    // get random number tht determine if we building
                    // minimum of 1 doorway or an extra doorway as well
                    int num = getRandomBtn(1, 2); // random to determine case
                    // This will always happen on any roll(satisfies the constraint)
                    if (num == 2 || num == 1)
                    {
                        buildRoomDoorway(id, side);
                    }
                    // the extra case
                    if (num == 1)
                    {
                        buildRoomDoorway(id, otherSide);
                    }
                }
            }
        }
    }
}

void Game::buildTopRooms()
{
    // for loop to check the ids of the rooms in the dungeon level
    for (int id = 1; id <= level->numberOfRooms(); id++)
    {
        // then check if there the id is that of a non-corner room
        if (level->isNonCornerRoom(id) == true)
        {
            // then check if id is that of a room in the top side
            if (level->isTopRoom(id) == true)
            {
                // Now we got our room,  time to build its doorways
                // another check for cases where width=1 or height=1
                if (level->width() == 1)
                {
                    // if its a one width dungeon we do not build top rows or bottom rows or mid rows
                    return; // function ends here
                }
                else
                {
                    // for an n by 1 case toprooms and bottom rooms will be the same thing,
                    // we will avoid their conflict by having to check if there already passage existing
                    // so no double building doorways if there should be any already
                    if (level->height() == 1)
                    {
                        // its a non corner room so can only connect east and west
                        // so we check and build 2 doorways
                        if (level->retrieveRoom(id)->edgeAt(Direction::East)->isPassage() == true)
                        {
                        }
                        else
                        {
                            builder->buildDoorway(level->retrieveRoom(id), level->retrieveNearbyRoom(id, Direction::East), Direction::East, getConstraint());
                        }
                        // build second doorways onto west
                        if (level->retrieveRoom(id)->edgeAt(Direction::West)->isPassage() == true)
                        {
                        }
                        else
                        {
                            builder->buildDoorway(level->retrieveRoom(id), level->retrieveNearbyRoom(id, Direction::West), Direction::West, getConstraint());
                        }
                        return; // function ends here
                    }
                }

                // we know if a room is on any side then it can only connect 3 ways (south, east and west)
                // we also do not need to check for entrance and exit here as this is not top or bottom xD

                int random = getRandomInt(1, 2); // random number to determing the constraint cases
                // List of the available directions we can connect
                std::vector<Direction> list = {Direction::South, Direction::East, Direction::West};
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                std::shuffle(begin(list), end(list), std::default_random_engine(seed)); // shuffles the directions list (to make the options random not fixed)

                // the constraint states to include the entrance doorway if the room has entrance
                // this is considered in the last case. means it is bound to be included whether random number is 2(by default) or 3
                if (random == 2)
                {
                    buildRoomDoorway(id, list.at(0));
                }
                // will always happen
                if (random == 2 || random == 1)
                {
                    buildRoomDoorway(id, list.at(1));
                    // check if this room has entrance, it includes its available entrance door
                    // in the minimum value
                    if (level->retrieveRoom(id)->hasEntrance() == true)
                    {
                        // does nothing because we consider the entrance as the minimum among the 2
                    }
                    else
                    {
                        buildRoomDoorway(id, list.at(2));
                    }
                }
            }
        }
    }
}
void Game::buildBottomRooms()
{
    // for loop to check the ids of the rooms in the dungeon level
    for (int id = 1; id <= level->numberOfRooms(); id++)
    {
        // then check if there the id is that of a non-corner room
        if (level->isNonCornerRoom(id) == true)
        {
            // then check if id is that of a room in the bottom side
            if (level->isBottomRoom(id) == true)
            {
                // NOTE:: there is no width or height check here because we only use buildToprooms
                // to handle the specific cases, this is ommitted

                // Now we got our room,  time to build its doorways
                // we know if a room is on any side then it can only connect 3 ways (north, east and west)
                // we also do not need to check for entrance and exit here as this is not top or bottom xD

                int random = getRandomInt(1, 2); // random number to determing the constraint cases
                // List of the available directions we can connect
                std::vector<Direction> list = {Direction::North, Direction::East, Direction::West};

                shuffle_list(list);
                //                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                //                std::shuffle(begin(list), end(list), std::default_random_engine(seed)); // shuffles the directions list (to make the options random not fixed)

                // the constraint states to include the exit doorway if the room has exit(occurs at bottom row)
                // this is considered in the last case. means it is bound to be included whether random number is 2 or 3
                if (random == 2)
                {
                    buildRoomDoorway(id, list.at(0));
                }
                // Always going to happen
                if (random == 2 || random == 1)
                {
                    buildRoomDoorway(id, list.at(1));
                    // check if this room has exit, it includes its available entrance door
                    // in the minimum value
                    if (level->retrieveRoom(id)->roomHasExit() == true)
                    {
                        // does nothing as we already consider the exit doorway as one of the minimum required of at least 2
                    }
                    else
                    {
                        buildRoomDoorway(id, list.at(2));
                    }
                }
            }
        }
    }
}
void Game::buildLeftRooms()
{
    // for loop to check the ids of the rooms in the dungeon level
    for (int id = 1; id <= level->numberOfRooms(); id++)
    {
        // then check if there the id is that of a non-corner room
        if (level->isNonCornerRoom(id) == true)
        {
            // then check if id is that of a room in the left side
            if (level->isLeftRoom(id) == true)
            {
                // another check for cases where width=1 or height=1
                //  Note:: Left rooms and right rooms are meant to be the same in such cases of width =1
                //  sp i decided to only consider handle the cases in one function (buildLeftRooms)
                if (level->width() == 1)
                {
                    // if height = 1 nothing happens(already handled)
                    if (level->height() > 1)
                    {
                        // if height =2 this wont happen because there will be 2 corner rooms
                        // and non of rooms in here are corner rooms, so this is for a case where
                        // likely height >2

                        // we only check and build doorways above and below (north and south)
                        if (level->retrieveRoom(id)->edgeAt(Direction::North)->isPassage() == true)
                        {
                            // there is a passage so dont build a doorway
                        }
                        else
                        {
                            builder->buildDoorway(level->retrieveRoom(id),
                                                  level->retrieveNearbyRoom(id, Direction::North),
                                                  Direction::North, getConstraint());
                        }
                        // Build a doorway to south
                        if (level->retrieveRoom(id)->edgeAt(Direction::South)->isPassage() == true)
                        {
                            // there is a passage so dont build a doorway
                        }
                        else
                        {
                            builder->buildDoorway(level->retrieveRoom(id),
                                                  level->retrieveNearbyRoom(id, Direction::South),
                                                  Direction::South, getConstraint());
                        }
                    }
                    return; // function ends here
                }
                else
                {
                    // we do not need to build to build any rooms here
                    // in a case of height=1

                    // IF ends
                }
                // Now we got our room,  time to build its doorways
                // we know if a room is on any side then it can only connect 3 ways (north, south and east)
                // we also do not need to check for entrance and exit here as this is not top or bottom xD

                int random = getRandomInt(1, 2); // random number to determing the constraint cases
                // List of the available directions we can connect
                std::vector<Direction> list = {Direction::North, Direction::South, Direction::East};
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                std::shuffle(begin(list), end(list), std::default_random_engine(seed)); // shuffles the directions list (to make the options random not fixed)
                if (random == 2)
                {
                    buildRoomDoorway(id, list.at(0));
                }
                // always happen
                if (random == 2 || random == 1)
                {
                    buildRoomDoorway(id, list.at(1));
                    buildRoomDoorway(id, list.at(2));
                }
            }
        }
    }
}
void Game::buildRightRooms()
{
    // for loop to check the ids of the rooms in the dungeon level
    for (int id = 1; id <= level->numberOfRooms(); id++)
    {
        // then check if there the id is that of a non-corner room
        if (level->isNonCornerRoom(id) == true)
        {
            // then check if id is that of a room in the right side
            if (level->isRightRoom(id) == true)
            {
                // THERE IS NO WIDTH AND HEIGHT CHECK HERE
                // reason being that cases for right rooms and left rooms are same and in such
                // cases only one function is needed

                // Now we got our room,  time to build its doorways
                // we know if a room is on any side then it can only connect 3 ways (north, south and west)
                // we also do not need to check for entrance and exit here as this is not top or bottom xD

                int random = getRandomInt(1, 2); // random number to determing the constraint cases
                // List of the available directions we can connect
                std::vector<Direction> list = {Direction::North, Direction::South, Direction::West};
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                std::shuffle(begin(list), end(list), std::default_random_engine(seed)); // shuffles the directions list (to make the options random not fixed)
                if (random == 2)
                {
                    buildRoomDoorway(id, list.at(0));
                }
                if (random == 2 || random == 1)
                {
                    buildRoomDoorway(id, list.at(1));
                    buildRoomDoorway(id, list.at(2));
                }
            }
        }
    }
}
void Game::buildMidRooms()
{
    for (int id = 1; id <= level->numberOfRooms(); id++)
    {
        if (level->isMidRoom(id))
        {
            // NOTE: cases of 1x1, 1xn, and nx1 do not involve this function
            // because this function only deals with rooms that can connect in all directions
            // whereas the cases do not do that

            // first we get a random number between 2 and 4
            // as we now we need a minimum of 2 connections and maximum of 4 connections for mid rooms
            int randNum = getRandomInt(1, 3);
            // vector of 4 different random numbers 0-3 (used to cast to direction)
            std::vector<Direction> list = {Direction::East, Direction::West, Direction::South, Direction::North};
            // reshuffle
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(begin(list), end(list), std::default_random_engine(seed));
            // We make cases

            // if 4 then build 4 doorways
            if (randNum == 3)
            {
                buildRoomDoorway(id, static_cast<Direction>(list.at(0)));
            }
            if (randNum == 3 || randNum == 2)
            {
                buildRoomDoorway(id, static_cast<Direction>(list.at(1)));
            }
            // case always happens
            if (randNum == 3 || randNum == 2 || randNum == 1)
            {
                // when any number rolls up then we must build 2 doorways unless there is a connection existing already
                // check if there is already a passage existing then we do nothing
                buildRoomDoorway(id, static_cast<Direction>(list.at(2)));
                buildRoomDoorway(id, static_cast<Direction>(list.at(3)));
            }
        }
    }
}

void Game::buildRandomEntrance()
{
    // Since this class build entrance first there is no need to check if there is an exit
    // if check to see entranceID is that of a corner room or non-corner room
    // if true apply pick random direction choice

    int last = level->width();                  // length of the first row
    int start = 1;                              // first id will always be 1
    int entranceID = getRandomInt(start, last); // random id from first row

    // We must give the entrance a freedom or random any side when the width=1
    if (level->width() == 1)
    {
        // if height ==1 then we can chose any side to make entrance doorway
        if (level->height() == 1)
        {
            // assign the entrance anywhere at random
            builder->buildEntrance(level->retrieveRoom(entranceID), static_cast<Direction>(getRandomInt(0, 3)));
        }
        else
        {
            // otherwise we can only assign north,east or west
            std::vector<Direction> list = {Direction::North, Direction::East, Direction::West};
            // shuffle the list with directions
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(begin(list), end(list), std::default_random_engine(seed)); // shuffles the directions list (to make the options random not fixed)
            // pick one at random
            builder->buildEntrance(level->retrieveRoom(entranceID), list.at(getRandomInt(0, 2)));
        }
    }
    // if non of the case above occurs then we consider the normal approach below
    else
    {
        if (entranceID == start)
        { // if entrance id is equal to that of first corner
            // Direction either North or West (0 or 3)
            builder->buildEntrance(level->retrieveRoom(entranceID), static_cast<Direction>(getRandomBtn(0, 3)));
        }
        else if (entranceID == last)
        {
            // Direction either North or East
            builder->buildEntrance(level->retrieveRoom(entranceID), static_cast<Direction>(getRandomBtn(0, 2)));
        }
        else
        {
            // Direction can only be North
            builder->buildEntrance(level->retrieveRoom(entranceID), Direction::North);
        }
    }
}

void Game::buildRandomExit()
{
    // we know the last id = level->numberOfrooms()
    // the first id in last row= lastId-width+1
    int end = level->numberOfRooms();
    int begin = end - (level->width()) + 1;
    // we get a random number that represents a random id picked from the last row
    int randId = getRandomInt(begin, end);

    // we must consider a case where width =1
    if (level->width() == 1)
    {
        // also consider if height =1 (1x1 dungeon)
        if (level->height() == 1)
        {
            // pick random direction 0-3
            Direction random = static_cast<Direction>(getRandomInt(0, 3));
            // build an entrance at that edge/direction, but first check if there is already an entrance
            if (std::dynamic_pointer_cast<core::dungeon::Doorway>(level->retrieveRoom(randId)->edgeAt(random)))
            {
                if (std::dynamic_pointer_cast<core::dungeon::Doorway>(level->retrieveRoom(randId)->edgeAt(random))->isEntrance())
                {
                    // attempt to build the exit again until it does not happen
                    buildRandomExit(); // recursion
                }
            }
            // otherwise just build an exit doorway here
            builder->buildExit(level->retrieveRoom(randId), random);
            return; // end the function to avoid any further execution
        }
        else
        {
            // otherwise the height is greater than 1 we can also build exit at south, east or west(1-3)
            builder->buildExit(level->retrieveRoom(randId), static_cast<Direction>(getRandomInt(1, 3)));
            return;
        }
    }
    // There is a case where we have many columns in one row, we need to avoid entrance and
    // exit to be picked on the same room
    else if ((level->height() == 1) && (level->width() > 1))
    {
        // check if room already has entrance then re-call the function until a different room is picked
        if (level->retrieveRoom(randId)->hasEntrance() == true)
        {
            buildRandomExit(); // recursion
        }
        else
        {
            // otherwise check if edge if free to make exit and make exit
            Direction randomDirection = static_cast<Direction>(getRandomInt(0, 3));
            // check if there is a neighbouring room at that direction, if there isnt then good place
            // to make exit
            while (level->retrieveNearbyRoom(randId, randomDirection) != nullptr)
            {
                // pick another random direction until we find a free one
                randomDirection = static_cast<Direction>(getRandomInt(0, 3));
            }
            builder->buildExit(level->retrieveRoom(randId), randomDirection);
        }
    }
    else
    {
        // check if the random id is that of a corner room (begin and end are corner ids already)
        if (randId == begin)
        { // first corner at the bottom
            // Direction either south or west(get random number either 1 or 3)
            builder->buildExit(level->retrieveRoom(randId), static_cast<Direction>(getRandomBtn(1, 3)));
        }
        else if (randId == end)
        { // check if random id is that of right corner
            // Direction either south or east ( 1 or 2)
            builder->buildExit(level->retrieveRoom(randId), static_cast<Direction>(getRandomBtn(1, 2)));
        }
        else
        {
            // Otherwise randId isnt that of a corner room thus direction can only be south
            builder->buildExit(level->retrieveRoom(randId), Direction::South);
        }
    }
}

int Game::getRandomInt(int min, int max)
{
    // no need to generate random number
    if (min == max)
    {
        return max;
    }
    if (max < min)
    {
        std::swap(min, max);
    }

    return (int)(randomDouble() * (max - min + 1)) + min;
}

int Game::getRandomBtn(int num1, int num2)
{
    int randNum = getRandomInt(1, 2);
    switch (randNum)
    {
    case 1:
        return num1;
        break;
    default:
        return num2;
        break;
    }
}

DLB::MoveConstraints Game::getConstraint()
{
    // constraint for the origin doorway
    MoveConstraints originC;
    // constraint for the destination room doorway
    MoveConstraints destC;

    originC = builder->getRandomOriginConstraint();
    destC = builder->getRandomDestConstraint();
    // general constraint set is returned(individual constraints added together)
    return originC | destC;
}

void Game::buildRoomDoorway(int id, Direction side)
{
    // check if there is a connection existing
    if ((level->retrieveRoom(id)->edgeAt(side)->isPassage()) == true)
    {
    }
    else
    {
        builder->buildDoorway(level->retrieveRoom(id), level->retrieveNearbyRoom(id, side), side, getConstraint());
    }
}

void Game::addRandomCreatures()
{
    // Loops throughout all rooms in the level
    for (int id = 1; id <= level->numberOfRooms(); id++)
    {
        // check if the room is an entrance (it is the first check
        if (level->retrieveRoom(id)->hasEntrance() == true)
        {
            // we do not add a monster on the entrance room

            // then check if it may also be an exit
            if (level->retrieveRoom(id)->roomHasExit() == true)
            {
                // we must have a monster in this room, so even if the past
                // entrance check was true(both entrance and exit) this must happen to overrule it
                // the added monster will overrule the 25% chance
                addMonster(id);
            }
        }
        // Otherwise apply the 25% chance rule
        else
        {
            addMonster(id);
        }
    }
}

void Game::addRandomItems()
{
    // Loops throughout all rooms in the level
    for (int id = 1; id <= level->numberOfRooms(); id++)
    {
        // check if the room is an entrance (it is the first check
        if (level->retrieveRoom(id)->hasEntrance() == true)
        {
            // we do not add an item on the entrance room

            // then check if it may also be an exit
            if (level->retrieveRoom(id)->roomHasExit() == true)
            {
                // we must have an item in this room, so even if the past
                // entrance check was true(both entrance and exit) this must happen to overrule it
                // the added monster will overrule the 35% chance
                addItem(id);
            }
        }
        // Otherwise apply the 35% chance rule
        else
        {
            addItem(id);
        }
    }
}

void Game::addMonster(int id)
{
    // get random number between 1-100(representing percentages)
    int randNum = getRandomInt(1, 100);
    // on a case if it is an exit room we set a different unique number 101
    // that means we wont depend on the random number and it is out of range
    if (level->retrieveRoom(id)->roomHasExit() == true)
    {
        randNum = 101;
    }
    if (randNum <= 25)
    {
        builder->buildCreature(level->retrieveRoom(id));
    }
    else if (randNum == 101)
    {
        builder->buildCreature(level->retrieveRoom(id));
    }
}

void Game::addItem(int id)
{
    // get random number between 1-100(representing percentages)
    int randNum = getRandomInt(1, 100);
    // on a case if it is an exit room we set a different unique number 101
    // that means we wont depend on the random number and it is out of range
    if (level->retrieveRoom(id)->roomHasExit() == true)
    {
        randNum = 101;
    }
    if (randNum <= 35)
    {
        // get and add the item
        addItemOfType(id, getRandomItemType());
    }
    else if (randNum == 101)
    {
        // get and add the item
        addItemOfType(id, getRandomItemType());
    }
}

void Game::addItemOfType(int id, std::shared_ptr<Item> item)
{

    //
    level->retrieveRoom(id)->setItem(item);
}

std::shared_ptr<Item> Game::getRandomItemType()
{
    // gets a random item in range of 1-100
    // 35% = when number is less than or equal to 35
    // 65% = when number is more than 35
    int randomNum = getRandomInt(1, 100);

    std::shared_ptr<Item> randomItem;
    randomItem = builder->getRandomItem();
    // 35% is a weapon
    if (randomNum <= 35)
    {
        // make sure the random item is a consumable otherwise get another one
        while (std::dynamic_pointer_cast<Weapon>(randomItem) == nullptr)
        {
            randomItem = builder->getRandomItem();
        }
        return randomItem;
    }
    else
    {
        // 65 % chance its a consumable

        // make sure the random item is a consumable otherwise get another one
        while (std::dynamic_pointer_cast<Consumable>(randomItem) == nullptr)
        {
            randomItem = builder->getRandomItem();
        }
        return randomItem;
    }
}

template <typename T>
void Game::shuffle_list(std::vector<T> &list)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(begin(list), end(list), std::default_random_engine(seed)); // shuffles the directions list (to make the options random not fixed)
}
