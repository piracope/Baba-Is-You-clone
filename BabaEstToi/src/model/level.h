#ifndef LEVEL_H
#define LEVEL_H

#include "gameobject.h"

#include <unordered_map>
#include <vector>

class Level{

    std::unordered_multimap<Position, GameObject> map;
    std::unordered_multimap<ObjectType, ObjectType>rules;
    unsigned width;
    unsigned height;
    bool isWon;

    public:
    Level(std::string);

    void movePlayer(Direction);
    std::string getState();
    bool Won();

    private:
    std::vector<ObjectType> getPlayerObject();
    std::vector<std::pair<Position, GameObject>> getAllOfType(ObjectType);
    bool canMove(Position,Direction);
    void buildRules();
    void applyRules();
};


#endif // LEVEL_H
