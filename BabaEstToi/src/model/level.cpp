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
    return y < other.y || y == other.y && x < other.x;
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

// USEFUL MAPS

std::unordered_map<std::string, ObjectType> strtotype // FIXME : le balancer ailleurs ou jsp
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

    // TODO : enlever ça
    rules_.insert({ObjectType::BABA, ObjectType::YOU});
    //rules_.insert({ObjectType::WALL, ObjectType::STOP});
    rules_.insert({ObjectType::ROCK, ObjectType::PUSH});

    //buildRules();
    //applyRules();

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

bool Level::canMove(const Position pos, const Direction dir)
{
    /*
        3. Pour chaque GameObject, on vérifie si le type de cet objet est concerné par une règle.
            * Si aucun élément n'a de règle associée, le mouvement est permis
            * Si sa catégorie est autre que ELEM, il sera d'office poussable. Le comportement est égal à celui défini plus bas.
    */


    // 1. Si pos + dir dépasse les limites de la map, elle retourne faux.
    const Position final {pos + dir};
    if(final.x < 0 || final.y < 0 || final.x >= width_ || final.y >= height_)
        return false;

    // 2. On récupère les GameObjects se trouvant à la position d'arrivée.
    const auto its {gamemap_.equal_range(final)};

    // 3. Pour chaque GameObject, on vérifie si le type de cet objet est concerné par une règle.

    decltype(its.first) toPush {gamemap_.end()};

    for (auto it {its.first}; it != its.second; ++it)
    {
        const auto rules {rules_.equal_range(it->second.getType())}; // on chope le type et ses regles
        for (auto rule {rules.first}; rule != rules.second; ++rule)
        {
            // 4. En fonction de l'Aspect de la règle, plusieurs actions seront effectuées
            auto asp {rule->second};
            if(asp == ObjectType::STOP) return false; // STOP : le mouvement est refusé
            if(asp == ObjectType::PUSH) toPush = it;
        }
    }

    /* Si on arrive ici c'est que soit :
     *  1. y a aucun élément à la position final
     *  2. y a aucune règle sur les éléments
     *  3. y a aucun STOP
     */

    // donc, si aucun PUSH non plus, c'est bon
    if(toPush == gamemap_.end()) return true;

    const auto objToPush {*toPush};

    //sinon, je check s'il est pushable.
    if(!canMove(final + dir, dir)) return false;
    else
    {
        const auto its {gamemap_.equal_range(objToPush.first)};
        auto it {its.first};
        while (it != its.second && it->second != objToPush.second) ++it;
        gamemap_.erase(it);

        gamemap_.insert({objToPush.first + dir, objToPush.second});
    }
    return true;
}

void Level::movePlayer(const Direction dir)
{
    if(isWon_) throw std::logic_error {"Cannot move when game is won."};

    // 1. Récupérer les types d'éléments contrôlables par le joueur
    const auto playertypes {getPlayerObjects()};

    if(playertypes.empty()) return;

    // 2. Pour chacun de ces types, récupérer les GameObjects de ce type
    std::vector<std::pair<Position, GameObject>> playerobjects {};
    for (const auto type : playertypes)
    {
        const auto obj {getAllOfType(type)};
        playerobjects.insert(playerobjects.end(), obj.begin(), obj.end());
    }

    // 3. Pour chaque élément, tester si bouger le GameObject est possible, et si oui, le déplacer dans la map.
    for (const auto& obj : playerobjects)
    {
        if(canMove(obj.first, dir))
        {
            const auto its {gamemap_.equal_range(obj.first)};
            auto it {its.first};
            while (it != its.second && it->second != obj.second) ++it; // FIXME : bouger a la chaine bouge le premier et dernier seulement
            gamemap_.erase(it);

            gamemap_.insert({obj.first + dir, obj.second});
        }
    }

    // 4. Reconstruire les règles
    //buildRules();

    // 5. Appliquer les règles
    //applyRules();
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
