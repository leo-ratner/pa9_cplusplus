#ifndef FUNGUS_H
#define FUNGUS_H

#include "plant.h"

//the fungus grows based on the "Conway's game of life"
//cellular automaton.
//I was gonna do a more complex one, but unfortunately I am limited to
//a boolean array, and GOL is by far the best 2-state CA out there.


class Fungus : public Plant
{
public:
    Fungus(std::string name);

    void grow();

private:
    bool areValid(int,int);
};

#endif // FUNGUS_H
