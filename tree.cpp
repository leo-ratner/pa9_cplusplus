#include "tree.h"

Tree::Tree(std::string name):Plant(name)
{
    //tree starts at bottom middle: magic numbers ahoy!
    plantType = pdt::TREE;
    grid[2][4] = true;
    growStage = 3;
}

void Tree::grow()
{
    if(growStage >= 0)
    {
        grid[2][growStage] = true;
        growStage--;
    }
}
