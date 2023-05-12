#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPixmap>
#include <QMovie>
#include "babahChar.h"

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
    this->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    _scene.clear();
    auto gamemap = baba_.getState();
    _scene.clear();
    for (int x = 0; x< 18; ++x) {
        for (int y = 0; y < 18; ++y) {
            auto range {gamemap.equal_range({x, y})};
            if(range.first != range.second)
            {
                auto tmp = range.first;
                decltype(tmp) toShow;
                while(tmp!=range.second){
                    if(tmp->second.getType() == model::ObjectType::BABA){
                        std::cout<<"joueur à la pos : " << tmp->first.x << ", " << tmp->first.y << std::endl;
                    }
                    _scene.addRect(26*x,26*y,26,26);
                    ++tmp;
                }
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    std::cout <<(char) event->key() << std::endl;
    if((char)event->key() == 'Z'){//doit être en uppercase
        baba_.move(model::Direction::UP);
        this->update();
    }
    if((char)event->key() == 'Q'){
        baba_.move(model::Direction::LEFT);
        this->update();
    }
    if((char)event->key() == 'S'){
        baba_.move(model::Direction::DOWN);
        this->update();
    }
    if((char)event->key() == 'D'){
        baba_.move(model::Direction::RIGHT);
        this->update();
    }
    if((char)event->key() == 'R'){
        baba_.restart();
        this->update();
    }
}

