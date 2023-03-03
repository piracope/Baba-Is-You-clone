#ifndef ENUM_H
#define ENUM_H

#include <ostream>

enum class Categorie{
    ELEM,
    TEXT,
    ASPECT
};

enum class ObjectType{
    ROCK,
    WALL,
    FLAG,
    METAL,
    GRASS,
    WATER,
    BABA,
    TEXT_ROCK,
    TEXT_WALL,
    TEXT_FLAG,
    TEXT_METAL,
    TEXT_GRASS,
    TEXT_WATER,
    TEXT_BABA,
    KILL,
    PUSH,
    STOP,
    WIN,
    SINK,
    YOU
};

enum class Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};


inline std::ostream & operator<<(std::ostream & out, Categorie cat)
{
    switch (cat) {
    case Categorie::ELEM:
        out << "ELEM";
        break;
    case Categorie::ASPECT:
        out << "ASPECT";
        break;
    case Categorie::TEXT:
        out << "TEXT";
        break;
    }
    return out;
}

inline std::ostream & operator<<(std::ostream & out, ObjectType type){

    switch (type) {
    case ObjectType::ROCK:
        out << "ROCK";
        break;
    case ObjectType::WALL:
        out << "WALL";
        break;
    case ObjectType::FLAG:
        out << "FLAG";
        break;
    case ObjectType::METAL:
        out << "METAL";
        break;
    case ObjectType::GRASS:
        out << "GRASS";
        break;
    case ObjectType::WATER:
        out << "WATER";
        break;
    case ObjectType::BABA:
        out << "BABA";
        break;
    case ObjectType::TEXT_ROCK:
        out << "TEXT_ROCK";
        break;
    case ObjectType::TEXT_WALL:
        out << "TEXT_WALL";
        break;
    case ObjectType::TEXT_FLAG:
        out << "TEXT_FLAG";
        break;
    case ObjectType::TEXT_METAL:
        out << "TEXT_METAL";
        break;
    case ObjectType::TEXT_GRASS:
        out << "TEXT_GRASS";
        break;
    case ObjectType::TEXT_WATER:
        out << "TEXT_WATER";
        break;
    case ObjectType::TEXT_BABA:
        out << "TEXT_BABA";
        break;
    case ObjectType::KILL:
        out << "KILL";
        break;
    case ObjectType::PUSH:
        out << "PUSH";
        break;
    case ObjectType::STOP:
        out << "STOP";
        break;
    case ObjectType::WIN:
        out << "WIN";
        break;
    case ObjectType::SINK:
        out << "SINK";
        break;
    case ObjectType::YOU:
        out << "YOU";
        break;
    }
    return out;
}

inline std::ostream & operator<<(std::ostream & out, Direction dir)
{
    switch(dir)
    {
    case Direction::RIGHT:
        out << 0;
        break;
    case Direction::UP:
        out << 1;
        break;
    case Direction::LEFT:
        out << 2;
        break;
    case Direction::DOWN:
        out << 3;
    }
    return out;
}





#endif // ENUM_H
