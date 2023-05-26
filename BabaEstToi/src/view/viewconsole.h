#ifndef VIEW_H
#define VIEW_H

#include "../observer/observer.h"
#include "../model/baba.h"

namespace view
{

class ViewConsole : public Observer
{
    model::Baba * baba_;
public:
    /**
     * @brief Make the view console
     * @param baba the model
     */
    explicit ViewConsole(model::Baba * baba);

    /**
     * @brief Destructor of the view makes the model forget
     */
    ~ViewConsole();

    /**
     * @brief update the view of the game by reading the state of the game
     * @param subject the model
     */
    void update(const Subject * subject) override;

    /**
     * @brief take the input of the player
     * @return the input of the player
     */
    std::string askLine();

    /**
     * @brief print an error
     * @param e the error to print
     */
    void printError(const std::string&);

    /**
     * @brief prints a help message
     */
    void printHelp();
};
}
#endif // VIEW_H
