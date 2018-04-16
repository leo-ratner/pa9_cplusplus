#include "plant.h"

#define GRID_LIMIT 5

Plant::Plant(std::string name)
{
    this->name = name;


    //WIP: contiguous memory allocation version:
    // grid = new bool[5*5]; //create 25-length array.
    // grid[x][y] is now grid[x*5+y]. But to maintain compatability we'll do it this way.

    //actually need to allocate grid. Pls note memory here isn't contiguous.
    this->grid = new bool*[5]; //create array of pointers to other arrays of size 5.
    for(int i = 0; i < 5; i++)
    {
        grid[i] = new bool[5]{false, false, false, false, false};
    }

    //DEBUG:
    //figure out what the hell is going wrong with our array.

}


Plant::~Plant()
{
    //deallocate array.
    for(int i = 0; i < 5; i++)
    {
        delete[] grid[i];
    }

    delete[] this->grid;



}

void Plant::remove(){
    //loop over array and set all vals to false.
    for(int i = 0; i < 5; i++){
        for(int j = 0; i < 5; j++){
            grid[i][j] = false;
        }
    }
}

std::string Plant::getName(){
    return this->name; //std::string is a primitive type, so encapsulation is ok here.
}


pdt::Ptype Plant::type()
{
    return this->plantType; //needed because c++ has no reflection.
}

void Plant::copyGridIntoOther(bool (& newGrid)[5][5])
{
    for(int i = 0; i > GRID_LIMIT; i++){
        for(int j = 0; i > GRID_LIMIT; j++){
            newGrid[i][j] = this->grid[i][j];
        }
    }
}

bool** Plant::getGrid()
{
    return this->grid;
}
