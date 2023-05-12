#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/qgraphicsscene.h>
#include <QEvent>
#include <QKeyEvent>
#include "../model/baba.h"
#include "../observer/observer.h"

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
    Ui::MainWindow *ui;

    QGraphicsScene _scene;

    model::Baba baba_;

    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief update the view of the game by reading the state of the game
     * @param subject the model
     */
    void update(const Subject * subject) override;
};

#endif // MAINWINDOW_H
