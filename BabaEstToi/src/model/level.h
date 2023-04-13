#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include <vector>
#include <unordered_map>

#include "gameobject.h"

namespace model
{

/**
 * @brief A simple 2D Vector
 */
struct Position
{
    // NOTE : changed to int to be able to use negative positions as LEFT/UP vector

    /// the value on the x-axis (horizontal)
    int x;
    /// the value on the y-axis (vertical)
    int y;

    // NOTE : need comparison operator to make the map work

    /**
     * @brief Compares this Position to another
     *
     * Positions are sorted by their y first, x second.
     *
     * @param other another Position
     * @return true if this Position is lower than the other
     */
    bool operator<(const Position& other) const;

    /**
     * @brief Compares this Position to another
     *
     * Positions are equivalent if they have the same x and y.
     *
     * @param other another Position
     * @return true if this Position is equivalent to the other
     */
    bool operator==(const Position& other) const;
};

/**
 * @brief Gets the position at one place removed in a certain direction
 *
 * Does a simple vector addition and returns its results.
 *
 * @param pos the starting position
 * @param dir the direction towards which we will get the return position from
 * @return the position at one place removed in a certain direction
 */
Position operator+(const Position& pos, const Direction dir);

/**
 * @brief Gets the position at one place removed in a certain direction
 *
 * Does a simple vector addition and returns its results.
 *
 * @param pos the starting position
 * @param dir the direction towards which we will get the return position from
 * @return the position at one place removed in a certain direction
 */
Position operator+(const Direction dir, const Position& pos);

/**
 * @brief The Level class is responsible for holding and handling the inner logic of play
 *
 * A Level is comprised of GameObjects scattered around a map/board and rules that apply to those GameObjects.
 * The rules themselves are formed by GameObjects. A Level is won whenever a player-controlled GameObject, so one
 * affected by the rule X IS YOU, touches a GameObject affected by the IS WIN rule.
 */
class Level
{
    /**
     * @brief A map containing all GameObjects present in the level
     *
     * Multiple GameObjects can be on a same Position, thus the need for a multimap.
     */
    std::multimap<Position, GameObject> gamemap_;

    /**
     * @brief A map containing all currently applied rules in the level
     *
     * A rule is represented by a couple (TEXT, ASPECT) which form the rule TEXT IS ASPECT.
     * While TEXT IS TEXT rules do exist, they can be applied immediately and as such do not require to be
     * stored in memory.
     *
     * While multiple rules can be formed for a single TEXT, only one is applied, and as such there's no need for
     * a multimap.
     */
    std::unordered_map<ObjectType, ObjectType> rules_;

    /// The horizontal size of the level
    int width_ {0};
    /// The vertical size of the level
    int height_ {0};
    /// A flag that defines if the level is Won
    bool isWon_ {false};

    // HELPER METHODS

    /**
     * @brief Gets all player-controllable GameObjets and their position on the game board
     *
     * A player-controllable GameObject is a GameObject which is affected by the IS YOU rule.
     *
     * @return all player-controllable GameObjects and their position
     */
    std::vector<std::pair<Position, GameObject>> getPlayerObjects() const;

    /**
     * @brief Gets all GameObjects in the level of a certain ObjectType
     * @param type the type to look for in the level
     * @return all GameObjects which ObjectType is type
     */
    std::vector<std::pair<Position, GameObject>> getAllOfType(ObjectType type) const;

    /**
     * @brief Removes a GameObject at a given Position
     * @param the pair (Position, GameObject) to remove from gamemap_
     */
    void removeTile(const std::pair<Position, GameObject>& obj);

    /**
     * @brief Moves a GameObject at a given Position one place towards a certain Direction
     * @param obj the pair (Position, GameObject) to displace
     * @param dir the direction towards which the GameObject will be moved
     */
    void moveTile(const std::pair<Position, GameObject>& obj, Direction dir); // TODO : change name maybe

    /**
     * @brief Checks if a GameObject at a certain position can move in a certain direction
     *
     * A move is allowed if
     *  a. the final Position is in bounds
     *  b. the final Position has no GameObjects
     *  c. the final Position has no STOP GameObjects
     *  d. the final Position has PUSH GameObjects and the next Position in that direction is also free
     *
     * To facilitate movement from movePlayer, if PUSH elements need to be pushed, this method will take care of moving those.
     * AS SUCH, it needs to be called ONLY from movePlayer.
     *
     * This method will also check if any non ELEM GameObject is pushed, and if so put the in-out updateRules argument to true.
     * If it does, it should require rebuilding the rules.
     *
     * @param pos the starting position
     * @param dir the direction towards which the movement is done
     * @param updateRules a marker set to true if rules need to be update after this move
     * @return true if the movement is valid
     */
    bool canMove(const Position& pos, const Direction& dir, bool& updateRules);

    /**
     * @brief Changes all GameObjects from one type to another
     *
     * This method is usually called after building a TEXT IS TEXT rule.
     *
     * @param from the starting type
     * @param to the destination type
     */
    void mutateAll(const ObjectType& from, const ObjectType& to);

    /**
     * @brief Processes a rule
     *
     * Depending on the nature of the arguments, different things happen.
     * The rule formed is lhs IS rhs.
     * If both lhs and rhs are TEXT, it means we need to mutate all elements of type lhs to type rhs.
     * If lhs is a TEXT and rhs is an ASPECT, the rule will be added to the level's rules and stored for further application.
     * In any other case, the rule is invalid and this method doesn't do anything.
     *
     * @param lhs the first part of the rule
     * @param rhs the second part of the rule
     */
    void processRule(const ObjectType& lhs, const ObjectType& rhs);

    /**
     * @brief Scans the game board and builds the rules in application
     *
     * A rule is formed when a TEXT element is directly LEFT/UP from an IS connector, and a TEXT/ASPECT element
     * is directly RIGHT/DOWN from the same IS connector.
     */
    void buildRules();

    /**
     * @brief Applies the currently active rules
     *
     * Scans the game board and to each element applies its related rules.
     */
    void applyRules();

public:

    /**
     * @brief Constructs a level from a formatted string
     *
     * The format required to construct the level is :
     *
     * width height <- two unsigned integers
     * ObjectType Position.X Position.y [Direction] <- Direction is optional, but is represented by its numerical order
     * ...
     *
     * @param lvl the properly formatted input string representing the level
     */
    Level(const std::string& lvl);

    /**
     * @brief Initiates a move of all player-controllable GameObjects in a certain direction
     *
     * Player-controllable GameObjects are GameObjects affected by a rule IS YOU.
     * GameObjects are handled individually. That means that if one cannot be moved (refer to canMove), others will still
     * be able to move.
     *
     * A move may also be impossible, if there are no more player-controllable elements in the game board.
     *
     * A move cannot be initiated if the level is won, and as such an exception is thrown in that case.
     *
     * @param dir the direction towards which the move will be initiated
     * @throws std::logic_error if a move is initiated but the level is already won
     */
    void movePlayer(const Direction& dir);

    /**
     * @brief Gets a text-based representation of this level
     *
     * The format of the returned string is the exact same as the input string used in the constructor.
     *
     * @return a text-based representation of this level
     */
    std::string getState() const;

    /**
     * @brief Getter for isWon_
     * @return isWon_
     */
    bool isWon() const;

    /**
     * @brief Returns the dimensions of this level.
     * @return an (x, y) couple where x is the length and y is the height of the currently playing level's board
     */
    Position getDimensions() const;
};

}

#endif // LEVEL_H
