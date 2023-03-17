#include <string>
#include <sstream>
#include <unordered_map>
#include <stdexcept>

#include "level.h"

namespace model
{

// POSITION

bool Position::operator<(const Position& other) const
{
    return x < other.x || x == other.x && y < other.y;
}

Position operator+(const Position& pos, const Direction dir)
{
    static std::unordered_map<Direction, Position> dirToVector
    {
        {Direction::DOWN, {0, 1} },
        {Direction::LEFT, {-1, 0}},
        {Direction::RIGHT, {1, 0}},
        {Direction::UP, {0, -1}}
    };

    return {pos.x + dirToVector.at(dir).x, pos.y + dirToVector.at(dir).y};
}
Position operator+(const Direction dir, const Position& pos)
{
    return pos + dir;
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
    {"IS", ObjectType::IS},
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

// CONSTRUCTOR

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
        const ObjectType type { strtotype.at(tmp2) }; // first word -> type

        std::getline(line, tmp2, ' ');
        int x {std::stoi(tmp2)}; // second word -> pos.x

        std::getline(line, tmp2, ' ');
        int y {std::stoi(tmp2)}; // third word -> pos.y

        // TODO : direction
        gamemap_.insert({{x, y}, type}); // we add a GameObject (implicit constr) at (x, y)
    }

}

// HELPER METHODS

std::unordered_set<ObjectType> Level::getPlayerObjects() const
{
    std::unordered_set<ObjectType> ret {};
    for (const auto& [type, asp] : rules_)
    {
        if(asp == ObjectType::YOU) ret.insert(type);
    }

    return ret;
}

std::vector<std::pair<Position, GameObject>> Level::getAllOfType(ObjectType type) const
{
    std::vector<std::pair<Position, GameObject>> ret {};
    for (const auto &p : gamemap_)
    {
        if(p.second.getType() == type) ret.push_back(p);
    }

    return ret;
}

// MOVEMENT

void Level::movePlayer(Direction dir) {
    if(isWon_) throw std::logic_error {"Cannot move when game is won."};
    // TODO : tout le reste
}

// GETTERS

std::string Level::getState() const
{
    std::ostringstream ret {};
    ret << width_ << ' ' << height_ << std::endl;
    for (const auto& [pos, obj] : gamemap_)
    {
        ret << obj << ' ' << pos.x << ' ' << pos.y;
        if (obj.getDirection() != Direction::RIGHT) ret << ' ' << obj.getDirection();
        ret << std::endl;
    }

    return ret.str();
}

bool Level::isWon() const { return isWon_; }

Position Level::getDimensions() const { return Position {width_, height_}; }

}
