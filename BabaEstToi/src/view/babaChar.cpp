#include "babahChar.h"

BabaChar::BabaChar(QGraphicsItem *parent, int x, int y): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(""));
    setPos(x,y);
}

