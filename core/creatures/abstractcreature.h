#ifndef ABSTRACTCREATURE_H
#define ABSTRACTCREATURE_H
#include <memory>

namespace  core{
namespace  creatures{

/**
 * @class AbstractCreature
 * @brief The AbstractCreature class. Represents a general creature
 * that may exist in a room in a dungeon level. This class also employs a
 * prototype design pattern.
 *
 * @author Cassian Kahema
 */
class AbstractCreature
{
protected:
    /**
     * @brief creatureName The creature's name
     */
    std::string creatureName;
    /**
     * @brief character Character representation of the creature
     */
    char character;
public:
    /**
     * @brief AbstractCreature Default constructor
     */
    AbstractCreature();
    /**
     * @brief AbstractCreature Parametarized constructor that
     * assigns a name to the createure
     * @param name Name of the creature
     */
    AbstractCreature(const std::string &name);
    /**
     * @brief ~AbstractCreature Virtual Deconstructor
     */
    virtual ~AbstractCreature(){}
    /**
     * @brief clone Allows concrete creature types to clone
     * themselves
     * @return A cloned copy of a creature
     */
    virtual std::unique_ptr<AbstractCreature> clone() const=0;
    /**
     * @brief name Returns a creature's name
     * @return Name of the creature
     */
    std::string name();
    /**
     * @brief displayCharacter Returns character representation
     * of the creature
     * @return Character of creature
     */
    char displayCharacter();

};
}
}


#endif // ABSTRACTCREATURE_H
