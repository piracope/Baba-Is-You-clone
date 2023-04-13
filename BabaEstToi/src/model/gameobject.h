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
    GameObject(ObjectType, Direction = Direction::RIGHT);
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
