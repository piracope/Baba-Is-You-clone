#include <string>
#include <sstream>
#include <unordered_map>

#include "level.h"

// POSITION

bool Position::operator<(const Position& other) const
{
    return x < other.x || x == other.x && y < other.y;
}

// USEFUL MAPS

std::unordered_map<std::string, ObjectType> strtotype
{
    {"ROCK", ObjectType::ROCK},
    {"WALL", ObjectType::WALL},
    {"FLAG", ObjectType::FLAG},
    {"METAL", ObjectType::METAL},
    {"GRASS", ObjectType::GRASS},
    {"WATER", ObjectType::WATER},
    {"BABA", ObjectType::BABA},
    {"TEXT_ROCK", ObjectType::TEXT_ROCK},
    {"TEXT_WALL", ObjectType::TEXT_WALL},
    {"TEXT_FLAG", ObjectType::TEXT_FLAG},
    {"TEXT_METAL", ObjectType::TEXT_METAL},
    {"TEXT_GRASS", ObjectType::TEXT_GRASS},
    {"TEXT_WATER", ObjectType::TEXT_WATER},
    {"TEXT_BABA", ObjectType::TEXT_BABA},
    {"KILL", ObjectType::KILL},
    {"PUSH", ObjectType::PUSH},
    {"STOP", ObjectType::STOP},
    {"WIN", ObjectType::WIN},
    {"SINK", ObjectType::SINK},
    {"YOU", ObjectType::YOU}
};

Level::Level(std::string lvl)
{
    std::istringstream str {lvl};

    /* getting the dimensions */
    std::string tmp;
    std::getline(str, tmp);

    size_t pos = 0;
    width_ = std::stoi(tmp, &pos); // first word -> width
    ++pos;
    height_ = std::stoi(tmp.substr(pos), &pos); // second -> height

    while(std::getline(str, tmp))
    {
        std::istringstream line {tmp};

        std::string tmp2;
        std::getline(line, tmp2, ' ');
        auto type {strtotype.at(tmp2)}; // first word -> type

        std::getline(line, tmp2, ' ');
        unsigned x = std::stoi(tmp2); // second word -> pos.x

        std::getline(line, tmp2, ' ');
        unsigned y = std::stoi(tmp2); // third word -> pos.y

        // TODO : direction

        gamemap_.insert({{x, y}, type}); // we add a GameObject (implicit constr) at (x, y)
    }

}

bool Level::isWon() const
{
    return isWon_;
}

Position Level::getDimensions() const
{
    return Position {width_, height_};
}