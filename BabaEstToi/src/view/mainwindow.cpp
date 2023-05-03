#include "mainwindow.h"
#include "ui_mainwindow.h"
 #include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    _scene(this),
    baba_{model::Baba{}}
{
    ui->setupUi(this);

    QRect viewContentsRect = ui->myGraphicsView->contentsRect();
    _scene.setSceneRect(viewContentsRect);
     ui->myGraphicsView->setScene(&_scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addRect_clicked()
{
    _scene.addRect(50,50,50,50);
    std::cout << "Succes" << std::endl;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    std::cout <<(char) event->key() << std::endl;
    if((char)event->key() == 'Z'){//doit être en uppercase
        baba_.move(model::Direction::UP);
    }
    if((char)event->key() == 'Q'){
        baba_.move(model::Direction::LEFT);
    }
    if((char)event->key() == 'S'){
        baba_.move(model::Direction::DOWN);
    }
    if((char)event->key() == 'D'){
        baba_.move(model::Direction::RIGHT);
    }
}
