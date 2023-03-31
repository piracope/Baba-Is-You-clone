#include <unordered_map>
#include <ostream>

#include "enum.h"

namespace model
{

std::string to_string(Categorie cat)
{
    // FIXME : probably unused
    const static std::unordered_map<Categorie, std::string> cattostr
    {
        {Categorie::ELEM, "ELEM"},
        {Categorie::ASPECT, "ASPECT"},
        {Categorie::TEXT, "TEXT"},
    };

    return cattostr.at(cat);
}

std::string to_string(ObjectType type)
{
    const static std::unordered_map<ObjectType, std::string> typetostr
    {
        {ObjectType::ROCK, "ROCK"},
        {ObjectType::WALL, "WALL"},
        {ObjectType::FLAG, "FLAG"},
        {ObjectType::METAL, "METAL"},
        {ObjectType::GRASS, "GRASS"},
        {ObjectType::WATER, "WATER"},
        {ObjectType::BABA, "BABA"},
        {ObjectType::IS, "IS"},
        {ObjectType::TEXT_ROCK, "TEXT_ROCK"},
        {ObjectType::TEXT_WALL, "TEXT_WALL"},
        {ObjectType::TEXT_FLAG, "TEXT_FLAG"},
        {ObjectType::TEXT_METAL, "TEXT_METAL"},
        {ObjectType::TEXT_GRASS, "TEXT_GRASS"},
        {ObjectType::TEXT_WATER, "TEXT_WATER"},
        {ObjectType::TEXT_BABA, "TEXT_BABA"},
        {ObjectType::TEXT_BABA, "TEXT_BABA"},
        {ObjectType::KILL, "KILL"},
        {ObjectType::PUSH, "PUSH"},
        {ObjectType::STOP, "STOP"},
        {ObjectType::WIN, "WIN"},
        {ObjectType::SINK, "SINK"},
        {ObjectType::YOU, "YOU"}
    };

    return typetostr.at(type);
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
    // TODO : a bit lazy to make it a map fr
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
