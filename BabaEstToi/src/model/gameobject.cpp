#include "gameobject.h"

namespace model
{

// CONSTRUCTORS

GameObject::GameObject(ObjectType type, Categorie cat, Direction dir)
    : cat_{cat}, type_{type}, dir_{dir}
{}

GameObject::GameObject(ObjectType type, Direction dir)
    : type_ {type}, dir_ {dir}
{
    if(type < ObjectType::TEXT_ROCK) cat_ = Categorie::ELEM;
    else if(type < ObjectType::KILL) cat_ = Categorie::TEXT;
    else cat_ = Categorie::ASPECT;
}

// GETTERS & SETTERS

Categorie GameObject::getCategorie() const { return cat_; }
ObjectType GameObject::getType() const { return type_; }
Direction GameObject::getDirection() const { return dir_; }

void GameObject::setDirection(Direction dir){ dir_ = dir; }

bool GameObject::operator==(GameObject other)
{
    return type_ == other.type_;
}

// STRING MANIPULATION

std::ostream & operator<<(std::ostream & out, const GameObject & obj)
{
    return out << obj.getType();
}
}
