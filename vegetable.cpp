#include "vegetable.h"

Vegetable::Vegetable(std::string name) : Plant(name)
{
    //veg starts at top middle. More magic numbers!
    plantType = pdt::VEGETABLE;
    grid[2][0] = true;
    growStage = 1;
}

void Vegetable::grow()
{
    if(growStage < 5)
    {
        grid[2][growStage] = true;
        growStage++;
    }
}
