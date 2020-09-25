#ifndef CONSUMEABLE_H
#define CONSUMEABLE_H
#include "item.h"

namespace  core{
namespace  items{

class Consumeable: public Item
{
public:
    Consumeable();
    Consumeable(const std::string &name);

    Item *clone() const override;
};
}
}
#endif // CONSUMEABLE_H
