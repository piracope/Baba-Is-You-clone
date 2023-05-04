#ifndef BABAHCHAR_H
#define BABAHCHAR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>



class BabaChar: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    BabaChar(QGraphicsItem * parent = 0, int x=0, int y=0);
};


#endif // BABAHCHAR_H
