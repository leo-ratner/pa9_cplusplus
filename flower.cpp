#include "flower.h"

#include <QDebug>

Flower::Flower(std::string name):Plant(name)
{
    plantType = pdt::FLOWER;
    //flower starts at center.
    grid[2][2] = true;
    qInfo() << "PLANTED AT CENTER?";

    //ok, so it's running. Let's print out all the data in our grid?


}


void Flower::grow()
{
    //first generate a reference copy, so we don't have concurrent modification problems.
    //todo: maybe use std::array?
    bool gRef[5][5];

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            gRef[i][j] = this->grid[i][j]; //this is annoying but kind of needed.
        }
    }

    // loop *again*, this time over gRef to generate the next growth stage.
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){
            if(gRef[y][x])
            {   //make sure we're not out of index, and grow.
                if(y-1 >= 0) grid[y-1][x] = true; //above
                if(y+1 < 5) grid[y+1][x] = true; //below
                if(x-1 >= 0) grid[y][x-1] = true; //left
                if(x+1 < 5) grid[y][x+1] = true; //right
            }
        }
    }

}
