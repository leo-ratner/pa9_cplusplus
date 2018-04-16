#ifndef VEGETABLE_H
#define VEGETABLE_H

#include "plant.h"

class Vegetable : public Plant
{
public:
    Vegetable(std::string name);
    void grow();

private:
    int growStage;
};

#endif // VEGETABLE_H
