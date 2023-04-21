#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/baba.h"
#include "../view/view.h"
// TODO : document controller
namespace controller
{
/**
 * @brief The Controller that links the console View to the model
 */
class Controller // FIXME : call it ConsoleController or something
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
    Controller();

    /**
     * @brief Main gameplay loop.
     *
     * Asks for user command and executes it on the model.
     */
    void play();
};

}
#endif // CONTROLLER_H
