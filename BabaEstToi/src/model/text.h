#ifndef TEXT_H
#define TEXT_H

#include "gameobject.h"

class Text: public GameObject{
    ObjectType refType_;

    public:
    inline Text(ObjectType, Categorie, unsigned);
    inline ObjectType getRefType();
};

// prototypes

inline std::ostream & operator<<(std::ostream & out, Text & text);


// méthode inline

Text::Text(ObjectType type, Categorie cat, unsigned dir)
    :GameObject(type,cat,dir)
{
    switch (type) {
        case ObjectType::TEXT_BABA:
            refType_ = ObjectType::BABA;
            break;
        case ObjectType::TEXT_FLAG:
            refType_ = ObjectType::FLAG;
            break;
        case ObjectType::TEXT_ROCK:
            refType_ = ObjectType::ROCK;
            break;
        case ObjectType::TEXT_WALL:
            refType_ = ObjectType::WALL;
            break;
        case ObjectType::TEXT_METAL:
            refType_ = ObjectType::METAL;
            break;
        case ObjectType::TEXT_GRASS:
            refType_ = ObjectType::GRASS;
            break;
        case ObjectType::TEXT_WATER:
            refType_ = ObjectType::WATER;
            break;
    }
}

ObjectType Text::getRefType(){
    return refType_;
}

// fonction inline

std::ostream & operator<<(std::ostream & out, Text & text){
    GameObject &  temp {text};
    return out << temp << ", Ref type " << text.getRefType();
}



#endif // TEXT_H
