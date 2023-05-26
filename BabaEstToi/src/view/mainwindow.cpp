#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMenuBar>
#include <QMessageBox>

namespace view
{
int MainWindow::TILE_SIZE {24};

MainWindow::MainWindow(model::Baba *model, controller::GuiController* controller, QWidget *parent) :
    QMainWindow {parent},
    ui {new Ui::MainWindow},
    _scene {this},
    _baba{model},
    _controller{controller}
{
    setupMenus();
    setupWindow();

    _baba->registerObserver(this);
    MainWindow::update(_baba);


}

void MainWindow::setupWindow()
{
    ui->setupUi(this);

    const auto dimensions {_baba->getDimensions()};

    const QRect viewContentsRect = QRect {0, 0, dimensions.x * TILE_SIZE, dimensions.y * TILE_SIZE};
    // NOTE : this assumes that all levels have the same size.

    _scene.setSceneRect(viewContentsRect); // set size of window
    ui->myGraphicsView->setBackgroundBrush(Qt::black); // auto fill background to black
    ui->myGraphicsView->setScene(&_scene);

    // fits the window to the content
    ui->myGraphicsView->adjustSize();
    this->setCentralWidget(ui->myGraphicsView);
    this->adjustSize();
}

void MainWindow::setupMenus()
{
    QMenu* file {this->menuBar()->addMenu("&File")};
    QAction* save {file->addAction("&Save")};
    QAction* load {file->addAction("&Load")};
    QAction* quit {file->addAction("&Quit")};


    QMenu* help = this->menuBar()->addMenu("&Help");
    QAction* commands {help->addAction("&Keyboard commands")};
    QAction* about {help->addAction("&About")};
    this->connect(about, &QAction::triggered, this, &MainWindow::about);
    this->connect(commands, &QAction::triggered, this, &MainWindow::help);
    this->connect(save, &QAction::triggered, this, &MainWindow::save);
    this->connect(load, &QAction::triggered, this, &MainWindow::load);
    this->connect(quit, &QAction::triggered, this, &QApplication::quit);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Baba Est Toi"),
                       tr("<b>Baba Est Toi</b> is a C++/Qt Widget port of Baba is You.<br>"
                          "Authors of the port : Ayoub Moufidi (58089), Zeki Ozkara (58143)"));
}

void MainWindow::help()
{
    QMessageBox::information(this, tr("Keyboard commands"),
                             tr("Move : arrow keys<br>"
                                "Restart : R<br>"
                                "Quit : Escape"));
}

void MainWindow::save()
{
    try
    {
        _controller->save();
    }
    catch (const std::ios_base::failure&)
    {
        QMessageBox::critical(this, tr("Error"), tr("Couldn't save to disk."));
    }


}

void MainWindow::load()
{
    try
    {
        _controller->load();
    }
    catch (const std::ios_base::failure&)
    {
        QMessageBox::critical(this, tr("Error"), tr("No save found."));
    }
    catch (...)
    {
        QMessageBox::critical(this, tr("Error"), tr("Couldn't parse the save file."));
    }

}

const QPixmap& MainWindow::getSprite(const model::ObjectType type) const
{
    using enum model::ObjectType;

    const static QPixmap spritesheet {":/resource/sprites/spritesheet.png"};

    static std::unordered_map<model::ObjectType, QPixmap> sprites {
        {BABA,       spritesheet.copy(0 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {ROCK,       spritesheet.copy(0 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {WALL,       spritesheet.copy(1 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {FLAG,       spritesheet.copy(2 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {METAL,      spritesheet.copy(3 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {GRASS,      spritesheet.copy(0 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {LAVA,       spritesheet.copy(1 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {WATER,      spritesheet.copy(2 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {IS,         spritesheet.copy(3 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {TEXT_ROCK,  spritesheet.copy(0 * TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {TEXT_WALL,  spritesheet.copy(1 * TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {TEXT_FLAG,  spritesheet.copy(2 * TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {TEXT_METAL, spritesheet.copy(3 * TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {TEXT_GRASS, spritesheet.copy(0 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {TEXT_LAVA,  spritesheet.copy(1 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {TEXT_WATER, spritesheet.copy(2 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {TEXT_BABA,  spritesheet.copy(3 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {KILL,       spritesheet.copy(0 * TILE_SIZE, 5 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {PUSH,       spritesheet.copy(1 * TILE_SIZE, 5 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {STOP,       spritesheet.copy(2 * TILE_SIZE, 5 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {WIN,        spritesheet.copy(3 * TILE_SIZE, 5 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {SINK,       spritesheet.copy(0 * TILE_SIZE, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {BEST,       spritesheet.copy(1 * TILE_SIZE, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE)},
        {YOU,        spritesheet.copy(2 * TILE_SIZE, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE)}
    };

    return sprites.at(type);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(const Subject * subject)
{
    const auto& gamemap {_baba->getState()};
    qDeleteAll(_scene.items()); // delete called on every pointer
    _scene.clear(); // we clear the whole screen
    for (const auto& pair : gamemap)
    {
        const int posX {pair.first.x};
        const int posY {pair.first.y};

        QGraphicsPixmapItem* p = new QGraphicsPixmapItem(getSprite(pair.second.getType()));
        p->setPos(TILE_SIZE * posX, TILE_SIZE * posY);
        _scene.addItem(p);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    _controller->handleUserInput(event);
    QMainWindow::keyPressEvent(event);
}


}
