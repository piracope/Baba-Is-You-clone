#include <array>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>

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


/**
 * @brief Returns the ObjectType of the same name as a given string
 * @param type the string to get the type of
 * @return the type of the same name as type
 */
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
        {"BEST", ObjectType::BEST},
        {"YOU", ObjectType::YOU}
    };

    return strtypemap.at(type);
}

/**
 * @brief Returns the ObjectType described by a given TEXT ObjectType
 *
 * If no such description is found, so if type is not a TEXT type, the sentinel value IS will be returned.
 *
 * @param type a TEXT
 * @return the ObjectType described by type, or IS if it's not found
 */
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

Level::Level(const std::string& lvl)
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

        int dir = 0;
        std::getline(line, tmp2, ' ');

        if(!line.eof()) dir = std::stoi(tmp2); // third word, if it exists -> direction

        gamemap_.insert({{x, y}, GameObject{type, Direction{dir}}}); // we add a GameObject (implicit constr) at (x, y)
    }

    buildRules();
    applyRules();
}

// HELPER METHODS

std::vector<std::pair<Position, GameObject>> Level::getPlayerObjects() const
{
    // we get the player-controlled types
    std::unordered_set<ObjectType> playertypes {};
    for (const auto& [type, asp] : rules_)
    {
        if(asp == ObjectType::YOU) playertypes.insert(type);
    }

    // and for each of them, get all the objects
    std::vector<std::pair<Position, GameObject>> playerobjects {};
    for (const auto type : playertypes)
    {
        const auto obj {getAllOfType(type)};
        /* NOTE : yeah, this scans the map for each playerType.
         * That said, it's either i scan the whole map for each type, or i
         * scan all types for each element in the map. So it's equivalent
         */

        playerobjects.insert(playerobjects.end(), obj.begin(), obj.end());
    }

    return playerobjects;
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

void Level::mutateAll(const ObjectType& from, const ObjectType& to)
{
    for (auto &p : gamemap_)
    {
        if(p.second.getType() == from) p.second = GameObject{to};
    }
}

void Level::processRule(const ObjectType& lhs, const ObjectType& rhs)
{
    const auto refType {getRefType(lhs)};
    if(refType == ObjectType::IS) return;

    if(rhs >= ObjectType::KILL) // NOTE : KILL is the first ASPECT
    {
        // FIXME : implement priority -> only inserting KILL if it isn't WIN
        rules_.insert({refType, rhs}); // if right part of the rule is an ASPECT, add to the rules
    }
    else if(rhs > ObjectType::IS) // ensures != ELEM
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

    // 2. get all IS connectors
    const auto is {getAllOfType(ObjectType::IS)};

    // 3. for each IS, check if horizontal rule exists
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
                if(it->second.getCategorie() == Category::TEXT)
                {
                    lhs = it->second.getType(); // we have our left part of the rule
                    it = its.second; // and we exit the loop (literally a break)
                }
                else ++it;
            }

            if(lhs != ObjectType::IS)
            {
                its = gamemap_.equal_range(obj.first + dir.second);
                auto it {its.first};
                while (it != its.second)
                {
                    // if one of them is a TEXT or ASPECT
                    if(it->second.getCategorie() != Category::ELEM)
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
}

void Level::removeTile(const std::pair<Position, GameObject>& obj)
{
    const auto its {gamemap_.equal_range(obj.first)};
    auto it {its.first};
    while (it != its.second && it->second != obj.second) ++it;
    if(it != its.second) gamemap_.erase(it);
}

void Level::applyRules()
{
    std::vector<std::pair<Position, GameObject>> playerobjects {getPlayerObjects()};

    std::vector<std::pair<Position, GameObject>> toRemove {};

    for (const auto &obj : gamemap_)
    {
        // if there are no rules, no point going further
        if(!rules_.contains(obj.second.getType())) continue;
        // FIXME : is continue/break alright with the teacher ?

        const auto asp {rules_.at(obj.second.getType())};
        if(asp == ObjectType::SINK)
        {
            // We need to loop through all elements just to make sure we aren't deleting a non-ELEM

            const auto its {gamemap_.equal_range(obj.first)};
            auto it {its.first};
            unsigned nb {0};
            bool shouldErase {true};
            while(it != its.second) {
                if (it->second.getCategorie() != Category::ELEM) shouldErase = false; // DON'T make the tile disappear if there's an !ELEM
                // !ELEM cannot disappear!!
                nb++;
                it++;
            }

            if(shouldErase && nb > 1) { // add to the death row only if the conditions are met
                toRemove.insert(toRemove.end(), its.first, its.second);
            }
        }
        else { // except SINK, we need to find if a pleyr is on it
            for(const auto& playerObj : playerobjects)
            {
                if(playerObj.first == obj.first)
                {
                    if(asp == ObjectType::WIN) // player-controllable on WIN
                    {
                        isWon_ = true;
                        return;
                    }
                    else if (asp == ObjectType::KILL) toRemove.push_back(playerObj); // player-controllable on KILL
                }
            }
        }
    }

    for(auto& byebye : toRemove) // at last, we remove everyone that needs to be removed
    {
        removeTile(byebye);
    }
}

// MOVEMENT

void Level::moveTile(const std::pair<Position, GameObject>& tile, const Direction& dir)
{
    const auto its {gamemap_.equal_range(tile.first)};
    auto it {its.first};
    while (it != its.second && it->second != tile.second) ++it;
    gamemap_.erase(it);

    // FIXME : i should use removeTile, but iterators and pointers make my brain hurt

    // TODO : UNCOMMENT AFTER VIEW IS FIXED
    //gamemap_.insert({tile.first + dir, tile.second})->second.setDirection(dir);
    gamemap_.insert({tile.first + dir, tile.second});
}

bool Level::canMove(const Position& pos, const Direction& dir, bool& updateRules)
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
        if(it->second.getCategorie() != Category::ELEM)
        {
            toPush = it;
            updateRules = true;
        }
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

    if(!canMove(final, dir, updateRules)) return false; // if not, move not allowed

    else moveTile(objToPush, dir); // we push the GameObject to its end position
    return true;
}

void Level::movePlayer(const Direction& dir)
{
    if(isWon_) throw std::logic_error {"Cannot move when game is won."};

    // 1. get player controlled types (X IS MOVE)
    // 2. for each of those types, get all GameObjects of that type
    std::vector<std::pair<Position, GameObject>> playerobjects {getPlayerObjects()};

    bool update = false;

    // 3. For each GameObject, check if end pos is free, and move it in the gamemap if applicable
    for (const auto& obj : playerobjects)
    {
        if(canMove(obj.first, dir, update)) moveTile(obj, dir);
    }

    // 4. rebuild the rules

    if(update) buildRules();

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
