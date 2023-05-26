#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/baba.h"
#include "../view/viewconsole.h"

namespace controller
{
/**
 * @brief The Controller that links the console View to the model
 */
class ConsoleController
{
    /**
     * @brief the model
     */
    model::Baba baba;

    /**
     * @brief the console view
     */
    view::ViewConsole view;

public:
    /**
     * @brief Creates and starts a new game.
     */
    ConsoleController();

    /**
     * @brief Main gameplay loop.
     *
     * Asks for user command and executes it on the model.
     */
    void play();
};

}
#endif // CONTROLLER_H
