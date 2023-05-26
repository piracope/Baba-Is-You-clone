#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <QKeyEvent>

#include "../model/baba.h"

namespace controller
{
/**
 * @brief The GuiController class that handles user interactions from a Qt Widget view.
 *
 * This class assumes that the display of the widget's window is handled externally, be it in the main class
 * or in the view itself.
 */
class GuiController
{
    /**
     * @brief The model this controller will interact with.
     */
    model::Baba *model;
public:
    /**
     * @brief Creates a controller meant for a Qt Widget view.
     * @param model thhe model this controller will interact with
     */
    GuiController(model::Baba *model);

    /**
     * @brief Asks the model to load the save file.
     * This method may throw std::ios_base::failure if the save file couldn't be found
     * or other various exceptions if the save file does exist but is malformed.
     *
     * We let the view handle those exceptions.
     */
    void load();

    /**
     * @brief Asks the model to save the game in the save file.
     * This method may throw std::ios_base::failure if writing to the disk is imopssible.
     *
     * We let the view handle those exceptions.
     */
    void save();

    /**
     * @brief Handles specific key presses to actions on the model.
     *
     * The handled key presses are :
     * - R -> Restart
     * - Escape -> Quit
     * - Arrow keys -> Move
     *
     * @param key the key press' event
     */
    void handleUserInput(QKeyEvent* key);

};
}


#endif // GUICONTROLLER_H
