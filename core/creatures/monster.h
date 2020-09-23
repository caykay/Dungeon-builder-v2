#ifndef MONSTER_H
#define MONSTER_H
#include "abstractcreature.h"

namespace  core{
namespace  creatures{



class Monster: public AbstractCreature
{
public:
    Monster();
    Monster(const std::string &name);

    void clone() const override;
};
}
}
#endif // MONSTER_H
