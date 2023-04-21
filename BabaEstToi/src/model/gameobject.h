#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "enum.h"

namespace model
{

/**
 * @brief A discrete element in the game world
 *
 * A GameObject is a single element on the game map.
 */
class GameObject
{
    /// The GameObject's Category
    Category cat_;
    /// The GameObject's type
    ObjectType type_;
    /// The direction towards which the GameObject is facing
    Direction dir_;

public:
    /**
     * @brief Creates a GameObject of a given type facing a certain direction
     *
     * As the Category is critical to the GameObject's behaviour in the game, it is
     * impossible to manually set it.
     *
     * @param type the GameObject's ObjectType
     * @param dir the direction towards which the GameObject will face
     */
    GameObject(const ObjectType& type, const Direction& dir = Direction::RIGHT);

    /**
     * @brief Getter for the Categorie
     * @return the GameObject's Categorie
     */
    Category getCategorie() const;

    /**
     * @brief Getter for the ObjectType
     * @return the GameObject's ObjectType
     */
    ObjectType getType() const;

    /**
     * @brief Getter for the Direction
     * @return the Direction towards which the GameObject is facing
     */
    Direction getDirection() const;

    /**
     * @brief Setter for the Direction
     * @param the Direction towards which the GameObject will face
     */
    void setDirection(const Direction& dir);

    /**
     * @brief Compares this GameObject to another
     *
     * Two GameObjects are equivalent if their ObjectTypes are identical
     *
     * @param another GameObject
     * @return true if both GameObjects are equivalent
     */
    bool operator==(const GameObject& other);

};

// string manipulation

std::ostream & operator<<(std::ostream&, const GameObject&);
}
#endif // GAMEOBJECT_H
