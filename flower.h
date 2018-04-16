#ifndef FLOWER_H
#define FLOWER_H

#include "plant.h"

class Flower : public Plant
{
public:
    Flower(std::string name);
    void grow();
};

#endif // FLOWER_H
