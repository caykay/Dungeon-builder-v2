#ifndef ABSTRACTCREATURE_H
#define ABSTRACTCREATURE_H
#include <memory>

namespace  core{
namespace  creatures{


class AbstractCreature
{
protected:
    std::string creatureName;
    char character;
public:
    AbstractCreature();
    AbstractCreature(const std::string &name);
    virtual ~AbstractCreature(){}

    virtual std::unique_ptr<AbstractCreature> clone() const=0;
    std::string name();
    char displayCharacter();

};
}
}


#endif // ABSTRACTCREATURE_H
