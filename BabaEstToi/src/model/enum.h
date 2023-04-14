#ifndef ENUM_H
#define ENUM_H

#include <ostream>

namespace model
{

/**
 * @brief The different Categories of GameObjects that exist.
 *
 * A GameObject's Category defines its behavior. ELEMs are subject to the game's rules, TEXT and ASPECT are always pushable
 * and cannot disappear from the game board. TEXT define other ELEMs and ASPECTs define rule behaviours.
 *
 * Technically, the IS object is from yet another Category, a CONNECTOR, but they will not be implemented in this project.
 */
enum class Category
{
    /// GameObjects subject to the game's rules
    ELEM,
    /// GameObjects that describe other ELEM GameObjects
    TEXT,
    /// GameObjects that describe behaviours applied to other ELEM GameObjects
    ASPECT
};

/**
 * @brief The different displayable types of GameObjects
 *
 * A GameObject's ObjectType defines what it factually is and how it should be displayed. For instance, a TEXT_ROCK describes all ROCK elements,
 * but should be displayed as a TEXT_ROCK. Thus its type is TEXT_ROCK.
 */
enum class ObjectType
{
    /// A Rock
    ROCK,
    /// A Wall
    WALL,
    /// A Flag
    FLAG,
    /// A decorative metallic ground
    METAL,
    /// A patch of grass
    GRASS,
    /// A pool of Lava
    LAVA,
    /// A pool of Water
    WATER,
    /// Our beloved bunny-cat thing
    BABA,
    /// Connector between two parts of a rule
    IS,
    /// Describes ROCK
    TEXT_ROCK,
    /// Describes WALL
    TEXT_WALL,
    /// Describes FLAG
    TEXT_FLAG,
    /// Describes METAL
    TEXT_METAL,
    /// Describes GRASS
    TEXT_GRASS,
    /// Describes LAVA
    TEXT_LAVA,
    /// Describes WATER
    TEXT_WATER,
    /// Desribes BABA
    TEXT_BABA,
    /// Removes any player-controlled GameObject that touches it
    KILL,
    /// Makes the GameObject pushable
    PUSH,
    /// Makes the GameObject impenetrable
    STOP,
    /// Makes the player win the level when it touches it
    WIN,
    /// Removes all GameObjects at its position whenever one touches it
    SINK,
    /// Makes things the best things ever :D
    BEST,
    /// Makes a GameObject player-controllable
    YOU,
};

/**
 * @brief All possible directions of movement
 */
enum class Direction
{
    /// The horizontally positive (1, 0) direction
    RIGHT,
    /// The vertically negative (0, -1) direction
    UP,
    /// The horizontally negative (-1, 0) direction
    LEFT,
    /// The vertically positive (0, 1) direction
    DOWN
};

/**
 * @brief Returns the Category's name
 * @param cat the Category to get the name from
 * @return the Category's name
 */
std::string to_string(Category cat);

/**
 * @brief Returns the ObjectType's name
 * @param type the ObjectType to get the name from
 * @return the ObjectType's name
 */
std::string to_string(ObjectType type);

// FIXME : documenting those << operators ??
std::ostream & operator<<(std::ostream& out, Category cat);
std::ostream & operator<<(std::ostream& out, ObjectType type);
std::ostream & operator<<(std::ostream& out, Direction dir);

}
#endif // ENUM_H
