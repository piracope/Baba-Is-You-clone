#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "../observer/observer.h"
#include "../model/baba.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget, public Observer
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    static int TILE_SIZE;

    Ui::MainWindow *ui;

    QGraphicsScene _scene;

    model::Baba baba_;

    const QPixmap& getSprite(const model::ObjectType);

    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief update the view of the game by reading the state of the game
     * @param subject the model
     */
    void update(const Subject * subject) override;
};

#endif // MAINWINDOW_H
