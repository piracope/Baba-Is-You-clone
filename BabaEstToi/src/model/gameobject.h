#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <ostream>

enum class Categorie{
    ELEM,
    TEXT,
    ASPECT
};

enum class ObjectType{
    ROCK,
    WALL,
    FLAG,
    METAL,
    GRASS,
    WATER,
    BABA,
    TEXT_ROCK,
    TEXT_WALL,
    TEXT_FLAG,
    TEXT_METAL,
    TEXT_GRASS,
    TEXT_WATER,
    TEXT_BABA,
    KILL,
    PUSH,
    STOP,
    WIN,
    SINK,
    YOU
};

enum class Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Position{
    unsigned x;
    unsigned y;
};

class GameObject{

    Categorie cat_;
    ObjectType type_;
    unsigned dir_;

    public:
    inline GameObject(ObjectType,Categorie,unsigned);
    inline Categorie getCategorie() const;
    inline ObjectType getType() const;
    inline unsigned getDirection() const;
    inline void setDirection(unsigned);
};

// prototypes

inline std::ostream & operator<<(std::ostream & out, GameObject & obj);

inline std::ostream & operator<<(std::ostream & out, Categorie cat);

inline std::ostream & operator<<(std::ostream & out, ObjectType type);

// méthode inline

GameObject::GameObject(ObjectType type,Categorie cat,unsigned dir)
    :cat_{cat},type_{type},dir_{dir}
{}

Categorie GameObject::getCategorie() const {
    return cat_;
}

ObjectType GameObject::getType() const {
    return type_;
}

unsigned GameObject::getDirection() const {
    return dir_;
}

void GameObject::setDirection(unsigned dir){
    dir_ = dir;
}

// fonction inline

std::ostream & operator<<(std::ostream & out, GameObject & obj){
    return out <<"Categorie "<< obj.getCategorie() << ", Type "<< obj.getType() << ", direction "<< obj.getDirection();
}

std::ostream & operator<<(std::ostream & out, Categorie cat){
    switch (cat) {
    case Categorie::ELEM:
        out << "ELEM";
        break;
    case Categorie::ASPECT:
        out << "ASPECT";
        break;
    case Categorie::TEXT:
        out << "TEXT";
        break;
    }
    return out;
}

std::ostream & operator<<(std::ostream & out, ObjectType type){

    switch (type) {
    case ObjectType::ROCK:
        out << "ROCK";
        break;
    case ObjectType::WALL:
        out << "WALL";
        break;
    case ObjectType::FLAG:
        out << "FLAG";
        break;
    case ObjectType::METAL:
        out << "METAL";
        break;
    case ObjectType::GRASS:
        out << "GRASS";
        break;
    case ObjectType::WATER:
        out << "WATER";
        break;
    case ObjectType::BABA:
        out << "BABA";
        break;
    case ObjectType::TEXT_ROCK:
        out << "TEXT_ROCK";
        break;
    case ObjectType::TEXT_WALL:
        out << "TEXT_WALL";
        break;
    case ObjectType::TEXT_FLAG:
        out << "TEXT_FLAG";
        break;
    case ObjectType::TEXT_METAL:
        out << "TEXT_METAL";
        break;
    case ObjectType::TEXT_GRASS:
        out << "TEXT_GRASS";
        break;
    case ObjectType::TEXT_WATER:
        out << "TEXT_WATER";
        break;
    case ObjectType::TEXT_BABA:
        out << "TEXT_BABA";
        break;
    case ObjectType::KILL:
        out << "KILL";
        break;
    case ObjectType::PUSH:
        out << "PUSH";
        break;
    case ObjectType::STOP:
        out << "STOP";
        break;
    case ObjectType::WIN:
        out << "WIN";
        break;
    case ObjectType::SINK:
        out << "SINK";
        break;
    case ObjectType::YOU:
        out << "YOU";
        break;
    }
    return out;
}


#endif // GAMEOBJECT_H
