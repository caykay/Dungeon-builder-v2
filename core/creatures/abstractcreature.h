#ifndef ABSTRACTCREATURE_H
#define ABSTRACTCREATURE_H
#include <memory>

namespace  core{
namespace  creatures{


class AbstractCreature
{
protected:
    std::string creatureName;
public:
    AbstractCreature();
    AbstractCreature(const std::string &name);
    virtual ~AbstractCreature(){}
    virtual std::unique_ptr<AbstractCreature> clone() const;
    std::string name();
    char displayCharacter();

};
}
}


#endif // ABSTRACTCREATURE_H
