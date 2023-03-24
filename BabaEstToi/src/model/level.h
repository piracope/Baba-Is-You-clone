#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include <vector>
#include <unordered_set>

#include "gameobject.h"

namespace model
{

struct Position
{
    int x; // NOTE : changed to int to be able to use negative positions as LEFT/UP vector
    int y;

    bool operator<(const Position&) const; // need comparison operator to make the map work
};

Position operator+(const Position&, const Direction);
Position operator+(const Direction, const Position&);

class Level
{
    std::multimap<Position, GameObject> gamemap_;
    std::map<ObjectType, ObjectType> rules_;
    int width_ {0};
    int height_ {0};
    bool isWon_ {false};

    std::unordered_set<ObjectType> getPlayerObjects() const;
    std::vector<std::pair<Position, GameObject>> getAllOfType(ObjectType) const;
    bool canMove(const Position, const Direction); // TODO
    void buildRules(); // TODO
    void applyRules(); // TODO

public:
    Level(std::string);

    void movePlayer(const Direction); // TODO
    std::string getState() const;
    bool isWon() const;
    Position getDimensions() const;
};

}

#endif // LEVEL_H
