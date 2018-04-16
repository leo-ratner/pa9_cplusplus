#ifndef PLANT_H
#define PLANT_H

#include "planttypes.h"
#include <string>
#include <vector>
#include <bitset>



class Plant
{
public:
    Plant(std::string name);
    virtual ~Plant();
    pdt::Ptype type();

    //unfortunately, do to wierdness, we need to set this to public. DO NOT MODIFY IT.
    //yes, I know this is *TERRIBLE* coding style, but I'm getting lazy.
    //bool grid[5][5];

    //now allocated dynamically.

    void copyGridIntoOther(bool (&newGrid)[5][5]);

    //std::vector<std::vector<bool>> getGrid()



protected:
    //bool grid[5][5];

    //ok, fuck it, we have to allocate it manually. ):

    bool** grid; //ugh double pointer.

    //std::vector<std::vector<bool>> grid;

    std::string name;
    pdt::Ptype plantType; //needed because C++ has no reflection.

public:
    void remove();
    virtual void grow(){}
    std::string getName();

    bool** getGrid();
};

#endif // PLANT_H
