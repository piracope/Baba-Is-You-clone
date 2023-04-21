#include "gameobject.h"

namespace model
{

// CONSTRUCTORS

GameObject::GameObject(const ObjectType& type, const Direction& dir)
    : type_ {type}, dir_ {dir}
{
    if(type < ObjectType::IS) cat_ = Category::ELEM;
    else if(type < ObjectType::KILL) cat_ = Category::TEXT;
    else cat_ = Category::ASPECT;
}

// GETTERS & SETTERS

Category GameObject::getCategorie() const { return cat_; }
ObjectType GameObject::getType() const { return type_; }
Direction GameObject::getDirection() const { return dir_; }

void GameObject::setDirection(const Direction& dir){ dir_ = dir; }

bool GameObject::operator==(const GameObject& other)
{
    return type_ == other.type_;
}

// STRING MANIPULATION

std::ostream & operator<<(std::ostream & out, const GameObject & obj)
{
    return out << obj.getType();
}
}
