#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/qgraphicsscene.h>
#include <Qevent>
#include <QKeyEvent>
#include "../model/baba.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addRect_clicked();
private:
    Ui::MainWindow *ui;

    QGraphicsScene _scene;

    model::Baba baba_;

    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
