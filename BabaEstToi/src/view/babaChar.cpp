#include "babahChar.h"

BabaChar::BabaChar(QGraphicsItem *parent, int x, int y): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap("C:/Users/ZEKI_/Downloads/baba"));
    setPos(x,y);
}

