#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "enum.h"

class GameObject{
    Categorie cat_;
    ObjectType type_;
    Direction dir_;

public:
    GameObject(ObjectType, Categorie, Direction);
    GameObject(ObjectType, Direction); //i'm trying out stuff
    Categorie getCategorie() const;
    ObjectType getType() const;
    Direction getDirection() const;
    void setDirection(Direction);
};

// string manipulation

std::ostream & operator<<(std::ostream&, const GameObject&);

#endif // GAMEOBJECT_H
