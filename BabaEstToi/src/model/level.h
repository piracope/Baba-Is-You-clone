#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include <vector>
#include <unordered_set>

#include "gameobject.h"

namespace model {
struct Position
{
    unsigned x;
    unsigned y;

    bool operator<(const Position&) const; // to make the map work
};

class Level
{
    // TODO : remettre une unordered_multimap (pas vraiment nécessaire en vrai)
    std::multimap<Position, GameObject> gamemap_;
    std::map<ObjectType, ObjectType> rules_;
    unsigned width_ {0};
    unsigned height_ {0};
    bool isWon_ {false};

    std::unordered_set<ObjectType> getPlayerObjects() const;
    std::vector<std::pair<Position, GameObject>> getAllOfType(ObjectType) const;
    bool canMove(Position,Direction);
    void buildRules();
    void applyRules();

public:
    Level(std::string);

    void movePlayer(Direction);
    std::string getState() const;
    bool isWon() const;
    Position getDimensions() const;
};
}

#endif // LEVEL_H
