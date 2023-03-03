#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "enum.h"

class GameObject{
    Categorie cat_;
    ObjectType type_;
    Direction dir_;

public:
    GameObject() = default; // racisme
    inline GameObject(ObjectType, Categorie, Direction);
    inline Categorie getCategorie() const;
    inline ObjectType getType() const;
    inline Direction getDirection() const;
    inline void setDirection(Direction);
};

// prototypes

inline std::ostream & operator<<(std::ostream & out, GameObject & obj);

// méthode inline

GameObject::GameObject(ObjectType type, Categorie cat, Direction dir)
    : cat_{cat}, type_{type}, dir_{dir}
{}

Categorie GameObject::getCategorie() const {
    return cat_;
}

ObjectType GameObject::getType() const {
    return type_;
}

Direction GameObject::getDirection() const {
    return dir_;
}

void GameObject::setDirection(Direction dir){
    dir_ = dir;
}

#endif // GAMEOBJECT_H
