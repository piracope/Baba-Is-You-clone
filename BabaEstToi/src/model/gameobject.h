#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "enum.h"

namespace model
{

class GameObject
{
    Categorie cat_;
    ObjectType type_;
    Direction dir_;

public:
    GameObject(ObjectType, Categorie, Direction);
    GameObject(ObjectType, Direction = Direction::RIGHT); //i'm trying out stuff
    Categorie getCategorie() const;
    ObjectType getType() const;
    Direction getDirection() const;
    void setDirection(Direction);

    bool operator==(GameObject);

};

// string manipulation

std::ostream & operator<<(std::ostream&, const GameObject&);
}
#endif // GAMEOBJECT_H
