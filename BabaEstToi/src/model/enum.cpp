#include <ostream>

#include "enum.h"

namespace model
{

std::string to_string(Categorie cat)
{
    switch (cat) {
    case Categorie::ELEM:
        return "ELEM";
    case Categorie::ASPECT:
        return "ASPECT";
    case Categorie::TEXT:
        return "TEXT";
    default:
        return "";
    }
}

std::string to_string(ObjectType type)
{
    switch (type) {
    case ObjectType::ROCK:
        return "ROCK";
    case ObjectType::WALL:
        return "WALL";
    case ObjectType::FLAG:
        return "FLAG";
    case ObjectType::METAL:
        return "METAL";
    case ObjectType::GRASS:
        return "GRASS";
    case ObjectType::WATER:
        return "WATER";
    case ObjectType::BABA:
        return "BABA";
    case ObjectType::IS:
        return "IS";
    case ObjectType::TEXT_ROCK:
        return "TEXT_ROCK";
    case ObjectType::TEXT_WALL:
        return "TEXT_WALL";
    case ObjectType::TEXT_FLAG:
        return "TEXT_FLAG";
    case ObjectType::TEXT_METAL:
        return "TEXT_METAL";
    case ObjectType::TEXT_GRASS:
        return "TEXT_GRASS";
    case ObjectType::TEXT_WATER:
        return "TEXT_WATER";
    case ObjectType::TEXT_BABA:
        return "TEXT_BABA";
    case ObjectType::KILL:
        return "KILL";
    case ObjectType::PUSH:
        return "PUSH";
    case ObjectType::STOP:
        return "STOP";
    case ObjectType::WIN:
        return "WIN";
    case ObjectType::SINK:
        return "SINK";
    case ObjectType::YOU:
        return "YOU";
    default:
        return "";
    }
}

std::ostream & operator<<(std::ostream & out, Categorie cat)
{
    return out << to_string(cat);
}

std::ostream & operator<<(std::ostream & out, ObjectType type)
{
    return out << to_string(type);
}

std::ostream & operator<<(std::ostream & out, Direction dir)
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

}
