#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "../observer/observer.h"
#include "../model/baba.h"
#include "../controller/guicontroller.h"

namespace Ui {
class MainWindow;
}

namespace view
{

/**
 * @brief The MainWindow class is a QMainWindow that will observe and display a BabaEstToi model.
 */
class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    /**
     * @brief Creates the MainWindow.
     * @param model the mdoel this view will observe
     * @param controller the controller user actions will be forwarded to
     * @param parent the parent QWidget, nullptr if this is the root window
     */
    explicit MainWindow(model::Baba *model, controller::GuiController *controller, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief Asks the controller to save the game, and displays an error message if an exception is thrown.
     */
    void save();
    /**
     * @brief Asks the controller to load the save file, and displays an error message if an exception is thrown
     */
    void load();
    /**
     * @brief Shows information about this application and its authors
     */
    void about();
    /**
     * @brief Shows keyboard commands and their effect.
     */
    void help();

private:
    /**
     * @brief The x and y size of one sprite in the sprite sheet.
     */
    static int TILE_SIZE;

    /**
     * @brief The QT designer-filled MainWindow.
     */
    Ui::MainWindow *ui;

    /**
     * @brief The scene that displays the board.
     */
    QGraphicsScene _scene;

    /**
     * @brief The model we will display.
     */
    model::Baba *_baba;

    /**
     * @brief The controller we will interact with.
     */
    controller::GuiController *_controller;

    /**
     * @brief Returns the QPixMap of the sprite of a specific ObjectType
     * @return the QPixMap of the sprite of a specific ObjectType
     */
    const QPixmap& getSprite(const model::ObjectType type) const;

    /**
     * @brief Sets up the menus and connects them to their slot.
     *
     * MENU STRUCTURE :
     *
     * File
     *      Save : saves the current state
     *      Load : loads the save file
     *      Quit : quits the application
     * Help
     *      Keyboard commands : shows a help message
     *      About : shows information about the app and its authors
     */
    void setupMenus();

    /**
     * @brief Sets up the window size and background color.
     */
    void setupWindow();

    /**
     * @brief Sends the key press to the controller for handling, then calls the base implementation.
     * @param event the key press event
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief update the view of the game by reading the state of the game
     * @param subject the model
     */
    void update(const Subject * subject) override;
};
}


#endif // MAINWINDOW_H
