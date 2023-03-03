#ifndef LEVEL_H
#define LEVEL_H

#include "gameobject.h"

#include <map>
#include <vector>

struct Position
{
    unsigned x;
    unsigned y;
};

class Level
{
    // TODO : remettre une unordered_multimap
    std::multimap<Position, GameObject> map;
    std::multimap<ObjectType, ObjectType> rules;
    unsigned width {0};
    unsigned height {0};
    bool isWon {false};

    std::vector<ObjectType> getPlayerObject();
    std::vector<std::pair<Position, GameObject>> getAllOfType(ObjectType);
    bool canMove(Position,Direction);
    void buildRules();
    void applyRules();

public:
    Level(std::string);

    void movePlayer(Direction);
    std::string getState();
    bool won();
};


#endif // LEVEL_H
