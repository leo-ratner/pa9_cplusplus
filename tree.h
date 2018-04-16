#ifndef TREE_H
#define TREE_H

#include "plant.h"

class Tree : public Plant
{
public:
    Tree(std::string name);
    void grow();

private:
    int growStage;

};

#endif // TREE_H
