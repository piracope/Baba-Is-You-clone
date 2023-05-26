#include "guicontroller.h"
#include <QApplication>
#include <QString>

namespace controller
{
GuiController::GuiController(model::Baba *model) : model {model}
{
}

void GuiController::load()
{
    model->load();
}

void GuiController::save()
{
    model->save();
}

void GuiController::handleUserInput(QKeyEvent* key)
{
    using enum model::Direction;

    switch (key->key())
    {
    case Qt::Key_Up:
        model->move(UP);
        break;
    case Qt::Key_Left:
        model->move(LEFT);
        break;
    case Qt::Key_Down:
        model->move(DOWN);
        break;
    case Qt::Key_Right:
        model->move(RIGHT);
        break;
    case Qt::Key_R:
        model->restart();
        break;
    case Qt::Key_Escape:
        QApplication::quit();
        break;
    }
}

}
