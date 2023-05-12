#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    _scene(this),
    baba_{model::Baba{}}
{
    ui->setupUi(this);

    QRect viewContentsRect = ui->myGraphicsView->contentsRect();
    _scene.setSceneRect(viewContentsRect);
    ui->myGraphicsView->setBackgroundBrush(Qt::black);
    ui->myGraphicsView->setScene(&_scene);
    baba_.registerObserver(this);
    MainWindow::update(&baba_);
}


QPixmap& getSprites(model::ObjectType type)
{
    static QPixmap spritesheet {"sprites/spritesheet.png"};
    static std::unordered_map<model::ObjectType, QPixmap> sprites {
        {model::ObjectType::BABA, spritesheet.copy(0, 0, 24, 24)}
    };

    return sprites.at(type);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(const Subject * subject)
{
    _scene.clear(); // we clear the whole screen
    const auto gamemap = baba_.getState();
    _scene.clear();
    for (const auto& pair : gamemap)
    {
        const int posX {pair.first.x};
        const int posY {pair.first.y};
        if(pair.second.getType() == model::ObjectType::BABA) {
            QGraphicsPixmapItem* p = new QGraphicsPixmapItem(getSprites(model::ObjectType::BABA));
            p->setPos(26*posX, 26*posY);
            _scene.addItem(p);
        }
        else
        {
            _scene.addRect(26*posX, 26*posY, 26, 26);
        }
    }
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
    if((char)event->key() == 'R'){
        baba_.restart();
    }
}

