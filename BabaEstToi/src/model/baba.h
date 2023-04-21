#ifndef BABA_H
#define BABA_H

#include <string>

#include "level.h"
#include "../observer/subject.h"

namespace model
{

/**
 * @brief The Façade of the model
 *
 * As the model's Façade, Baba serves as an entry point for all external classes to the game logic,
 * and is responsible for running the game and keeping it in a logical state.
 */
class Baba : public Subject
{
    /// The start of the path where levels are located and saved.
    inline static const std::string START_OF_PATH {"levels/level_"};
    // TODO : an env var would be so much better

    /// the number of the currently playing level
    unsigned lvlNumber_;

    /// the currently playing level
    Level lvl_;

    /**
     * @brief Starts a given level
     *
     * This method may fail if there is no level of the given number.
     *
     * @param num the level to start's number
     */
    void createLevel(unsigned nb);

    /**
     * @brief Creates a text representation of a level's map
     * @param gamemap the level's map
     * @return a text representation of a level's map
     */
    std::string buildLevelFromMap(const std::multimap<Position, GameObject> &gamemap) const;

public:

    /**
     * @brief Creates and launches the game
     *
     * On creation, starts and launches level n°0.
     */
    Baba();

    /**
     * @brief Restarts the currently playing level
     */
    void restart();

    /**
     * @brief Saves the current state of this level in memory
     *
     * There is at most one save at all times, and it is stored at START_OF_PATH + "S.txt".
     */
    void save() const;

    /**
     * @brief Loads a previously saved level
     */
    void load();

    /**
     * @brief Initiates a move from the player in a given Direction
     *
     * @param dir the move's direction
     */
    void move(Direction dir);

    /**
     * @brief Fetches the currently playing level's state
     *
     * @return the currently playing level's gamemap
     */
    std::multimap<Position, GameObject> getState() const;

    /**
     * @brief Returns the dimensions of the currently playing level.
     * @return an (x, y) couple where x is the length and y is the height of the currently playing level's board
     */
    Position getDimensions() const;
};

}

#endif // BABA_H
