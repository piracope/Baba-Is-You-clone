#ifndef ENUM_H
#define ENUM_H

#include <ostream>

namespace model
{
enum class Categorie
{
    ELEM,
    TEXT,
    ASPECT
};

enum class ObjectType
{
    ROCK,
    WALL,
    FLAG,
    METAL,
    GRASS,
    LAVA,
    WATER,
    BABA,
    IS,
    TEXT_ROCK,
    TEXT_WALL,
    TEXT_FLAG,
    TEXT_METAL,
    TEXT_GRASS,
    TEXT_LAVA,
    TEXT_WATER,
    TEXT_BABA,
    KILL,
    PUSH,
    STOP,
    WIN,
    SINK,
    YOU
};

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

std::string to_string(Categorie);
std::string to_string(ObjectType);

std::ostream & operator<<(std::ostream&, Categorie);
std::ostream & operator<<(std::ostream&, ObjectType);
std::ostream & operator<<(std::ostream&, Direction);

}
#endif // ENUM_H
