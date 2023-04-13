#include <string>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <iostream> // TODO : remove before release
#include <array>

#include "level.h"

namespace model
{

// POSITION

bool Position::operator<(const Position& other) const
{
    return y < other.y || y == other.y && x < other.x;
}

bool Position::operator==(const Position& other) const
{
    return x == other.x && y == other.y;
}
Position operator+(const Position& pos, const Direction dir)
{
    const static std::unordered_map<Direction, Position> dirToVector
    {
        {Direction::DOWN, {0, 1}},
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


ObjectType strToType(const std::string& type)
{
    const static std::unordered_map<std::string, ObjectType> strtypemap
    {
        {"ROCK", ObjectType::ROCK},
        {"WALL", ObjectType::WALL},
        {"FLAG", ObjectType::FLAG},
        {"METAL", ObjectType::METAL},
        {"GRASS", ObjectType::GRASS},
        {"LAVA", ObjectType::LAVA},
        {"WATER", ObjectType::WATER},
        {"BABA", ObjectType::BABA},
        {"IS", ObjectType::IS},
        {"TEXT_ROCK", ObjectType::TEXT_ROCK},
        {"TEXT_WALL", ObjectType::TEXT_WALL},
        {"TEXT_FLAG", ObjectType::TEXT_FLAG},
        {"TEXT_METAL", ObjectType::TEXT_METAL},
        {"TEXT_GRASS", ObjectType::TEXT_GRASS},
        {"TEXT_LAVA", ObjectType::TEXT_LAVA},
        {"TEXT_WATER", ObjectType::TEXT_WATER},
        {"TEXT_BABA", ObjectType::TEXT_BABA},
        {"KILL", ObjectType::KILL},
        {"PUSH", ObjectType::PUSH},
        {"STOP", ObjectType::STOP},
        {"WIN", ObjectType::WIN},
        {"SINK", ObjectType::SINK},
        {"YOU", ObjectType::YOU}
    };

    return strtypemap.at(type);
}

ObjectType getRefType(const ObjectType type)
{
    const static std::unordered_map<ObjectType, ObjectType> textToRefMap
    {
        {ObjectType::TEXT_ROCK, ObjectType::ROCK},
        {ObjectType::TEXT_WALL, ObjectType::WALL},
        {ObjectType::TEXT_FLAG, ObjectType::FLAG},
        {ObjectType::TEXT_METAL, ObjectType::METAL},
        {ObjectType::TEXT_LAVA, ObjectType::LAVA},
        {ObjectType::TEXT_GRASS, ObjectType::GRASS},
        {ObjectType::TEXT_WATER, ObjectType::WATER},
        {ObjectType::TEXT_BABA, ObjectType::BABA}
    };

    try
    {
        return textToRefMap.at(type);
    } catch (const std::out_of_range&)
    {
        return ObjectType::IS;
    }
}


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

    /* putting the objects */

    while(std::getline(str, tmp))
    {
        std::istringstream line {tmp};

        std::string tmp2;
        std::getline(line, tmp2, ' ');
        const ObjectType type { strToType(tmp2) }; // first word -> type

        std::getline(line, tmp2, ' ');
        int x {std::stoi(tmp2)}; // second word -> pos.x

        std::getline(line, tmp2, ' ');
        int y {std::stoi(tmp2)}; // third word -> pos.y

        // TODO : direction
        gamemap_.insert({{x, y}, type}); // we add a GameObject (implicit constr) at (x, y)
    }

    buildRules();
    applyRules();
}

// HELPER METHODS

std::unordered_set<ObjectType> Level::getPlayerTypes() const
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

void Level::mutateAll(const ObjectType from, const ObjectType to)
{
    for (auto &p : gamemap_)
    {
        if(p.second.getType() == from) p.second = GameObject{to};
    }
}

void Level::processRule(const ObjectType lhs, const ObjectType rhs)
{
    const auto refType {getRefType(lhs)};
    if(refType == ObjectType::IS) return;

    if(rhs >= ObjectType::KILL) // NOTE : KILL is the first ASPECT
    {
        rules_.insert({refType, rhs}); // if right part of the rule is an ASPECT, add to the rules
    }
    else if(rhs > ObjectType::IS)
    {
        // if not, mutate all tiles from left to right
        // BABA IS WALL => BABA becomes WALL
        const auto refTypeRight {getRefType(rhs)};
        if(refTypeRight != ObjectType::IS) mutateAll(refType, refTypeRight);
    }

}

void Level::buildRules()
{
    // 1. clear rules
    rules_.clear();

    //std::cout << "DEBUG | buildRules | Cleared rules" << std::endl;

    // 2. get all IS connectors
    const auto is {getAllOfType(ObjectType::IS)};

    //std::cout << "DEBUG | buildRules | Number of IS : " << is.size() << std::endl;

    // 3. for each IS, check if horizontal rule exists
    // TODO : optimization : keep in a set or something the position of every IS
    for (const auto& obj : is)
    {

        std::array<std::pair<Direction, Direction>, 2> dirs { // did this to not copypaste the code
            {
            {Direction::LEFT, Direction::RIGHT},
            {Direction::UP, Direction::DOWN}
        }};

        for(const auto& dir : dirs)
        {
            ObjectType lhs {ObjectType::IS}; // IS : sentinel value
            ObjectType rhs {ObjectType::IS};

            // we get the objects at the left
            auto its {gamemap_.equal_range(obj.first + dir.first)};
            auto it {its.first};
            while (it != its.second)
            {
                // if one of them is a TEXT
                if(it->second.getCategorie() == Categorie::TEXT)
                {
                    lhs = it->second.getType(); // we have our left part of the rule
                    it = its.second; // and we exit the loop (literally a break)
                }
                else ++it;
            }

            if(lhs != ObjectType::IS)
            {
                //std::cout << "DEBUG | buildRules | Found a LHS : " << lhs << std::endl;
                its = gamemap_.equal_range(obj.first + dir.second);
                auto it {its.first};
                while (it != its.second)
                {
                    // if one of them is a TEXT or ASPECT
                    if(it->second.getCategorie() != Categorie::ELEM)
                    {
                        rhs = it->second.getType(); // we have our right part of the rule
                        it = its.second; // and we exit the loop (literally a break)
                    }
                    else ++it;
                }
                // FIXME : DRY. but idk how to change this
            }

            if(rhs != ObjectType::IS) //if the rule was built
            {
                processRule(lhs, rhs); // process it
            }
        }
    }

    /*
    for(const auto &truc : rules_)
    {
        std::cout << truc.first << " IS " << truc.second << std::endl;
    }*/
}

void Level::removeTile(const std::pair<Position, GameObject>& obj)
{
    const auto its {gamemap_.equal_range(obj.first)};
    auto it {its.first};
    while (it != its.second && it->second != obj.second) ++it;
    gamemap_.erase(it);
}

void Level::applyRules()
{
    const auto playertypes {getPlayerTypes()}; // TODO : factorize this

    if(playertypes.empty()) return;

    std::vector<std::pair<Position, GameObject>> playerobjects {};
    for (const auto type : playertypes)
    {
        const auto obj {getAllOfType(type)};
        playerobjects.insert(playerobjects.end(), obj.begin(), obj.end());
    }

    for (auto &obj : gamemap_)
    {
        // FIXME : nested ifs -> decompose
        const auto rules {rules_.equal_range(obj.second.getType())}; // we get the rules aplied to this type
        for (auto rule {rules.first}; rule != rules.second; ++rule) // for each of them
        {
            auto asp {rule->second};
            if(asp == ObjectType::SINK) // FIXME : rearranged the priority, may not work!
            {
                if(gamemap_.count(obj.first) > 1)
                {
                    gamemap_.erase(obj.first);
                    return;
                }
            }

            for(const auto& playerObj : playerobjects)
            {
                if(playerObj.first == obj.first)
                {
                    if(asp == ObjectType::WIN)
                    {
                        isWon_ = true;
                        return;
                    }
                    else if (asp == ObjectType::KILL) removeTile(playerObj);
                }
            }
        }
    }
}

// MOVEMENT

void Level::moveTile(const std::pair<Position, GameObject>& tile, Direction dir)
{
    const auto its {gamemap_.equal_range(tile.first)};
    auto it {its.first};
    while (it != its.second && it->second != tile.second) ++it;
    gamemap_.erase(it);

    gamemap_.insert({tile.first + dir, tile.second});
    // TODO : change GameObject direction
}

bool Level::canMove(const Position pos, const Direction dir)
{
    // 1. if pos + dir is out of bounds, move not allowed
    const Position final {pos + dir};

    if(final.x < 0 || final.y < 0 || final.x >= width_ || final.y >= height_)
        return false;

    // 2. we get the GameObjects at the end position
    const auto its {gamemap_.equal_range(final)};

    decltype(its.first) toPush {gamemap_.end()}; // for storing the pointer to a potential pushable object

    // 3. for each GameObject, we check if rules apply to it
    for (auto it {its.first}; it != its.second; ++it)
    {
        if(it->second.getCategorie() != Categorie::ELEM) toPush = it;
        else // no rules can apply to a TEXT
        {
            const auto rules {rules_.equal_range(it->second.getType())}; // we get the rules aplied to this type
            for (auto rule {rules.first}; rule != rules.second; ++rule) // for each of them
            {
                // 4. behavior depends on aspect
                auto asp {rule->second};
                if(asp == ObjectType::STOP) return false; // STOP : the move is not allowed
                if(asp == ObjectType::PUSH) toPush = it; // PUSH : we store the pointer to push it later

                /* NOTE : if multiple pushable objects are on the same tile, only one will be pushed.
                 * this is the behavior from the reference executable, so we keep it like this.
                 */
            }
        }
    }

    // FIXME : i read a funny thing on cppreference and stackoverflow about pointers and iterators that are
    // not invalidated, so maybe this method is needlessly hard

    /* If we're still in this method :
     *  1. there are no GameObjects at the end position
     *  2. there are no rules applied to those GameObjects
     *  3. none of the rules are STOP
     */

    // thus, if no PUSH was encountered either, the move is allowed
    if(toPush == gamemap_.end()) return true;

    // we dereference the GameObject to push, as the pointer would become obsolete if a change is made to gamemap
    const auto objToPush {*toPush};

    // we need to check if the pushable can be pushed to the end pos

    if(!canMove(final, dir)) return false; // if not, move not allowed

    else moveTile(objToPush, dir); // we push the GameObject to its end position
    return true;
}

void Level::movePlayer(const Direction dir)
{
    if(isWon_) throw std::logic_error {"Cannot move when game is won."};

    // 1. get player controlled types (X IS MOVE)
    const auto playertypes {getPlayerTypes()};

    if(playertypes.empty()) return;

    // 2. for each of those types, get all GameObjects of that type
    std::vector<std::pair<Position, GameObject>> playerobjects {};
    for (const auto type : playertypes)
    {
        const auto obj {getAllOfType(type)};
        playerobjects.insert(playerobjects.end(), obj.begin(), obj.end());
    }

    // 3. For each GameObject, check if end pos is free, and move it in the gamemap if applicable
    for (const auto& obj : playerobjects)
    {
        if(canMove(obj.first, dir)) moveTile(obj, dir);
    }

    // 4. rebuild the rules
    buildRules();

    // TODO : only build rules if !ELEM moved
    // 5. apply the rules
    applyRules();
}

// GETTERS

std::string Level::getState() const
{
    std::ostringstream ret {};
    ret << width_ << ' ' << height_ << std::endl; // first line - dimensions
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
