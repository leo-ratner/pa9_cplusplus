#include "fungus.h"

Fungus::Fungus(std::string name) : Plant(name)
{
//initial starting configuration gives a set of cells that eventually decays into an oscillator.

    plantType = pdt::FUNGUS;

    const bool startState[5][5] =
    {
        {1,0,0,1,0},
        {0,1,0,0,0},
        {1,0,0,1,0},
        {0,1,0,1,1},
        {0,0,0,1,0}
    };

    //copy starting state into grid.
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            this->grid[i][j] = startState[i][j];
        }
    }
}

//GOL Rules (these apply to diagonals too, so a cell by default has 8 neigbors.
//the system assumes by that anything outside of the bounds does not add to neighbor count.

//anyways, on to the rules, pa from wikipedia!
/*
 * any live cell with <2 neighbors dies (underpopulation)
 * any live cell with 2 or 3 neighbors lives
 * any live cell with >3 neighbors dies (overpopulation)
 * any dead cell with *exactly* 3 neighbors becomes a living cell (reproduction)
*/


void Fungus::grow()
{
    bool ref[5][5] {0};

    //create a copy of the grid we can scan.
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            ref[i][j] = this->grid[i][j];
        }
    }

    //loop over grid, check neighbors, etc...
    for(int y = 0; y < 5; y++)
    {
        for(int x = 0; x < 5; x++)
        {
            int neighbors = 0;
            //count all the neighboring cells.

            //this is the ugliest code i've written in a long time.
            if(areValid(y-1, x-1) && ref[y-1][x-1]) neighbors++; //top left
            if(areValid(y-1, x) && ref[y-1][x])     neighbors++; //top middle
            if(areValid(y-1, x+1) && ref[y-1][x+1]) neighbors++; //top right

            if(areValid(y, x-1) && ref[y][x-1])     neighbors++; //straight left
            if(areValid(y, x+1) && ref[y][x+1])     neighbors++; //straight right

            if(areValid(y+1, x-1) && ref[y+1][x-1]) neighbors++; //bottom left
            if(areValid(y+1, x) && ref[y+1][x])     neighbors++; //bottom middle
            if(areValid(y+1, x+1) && ref[y+1][x+1]) neighbors++; //bottom right

            //now determine what we do based on neighbor count.

            if(ref[y][x]) //if the current cell is alive
            {
                if(neighbors < 2 || neighbors > 3){
                    this->grid[y][x] = false; //kill cell.
                }
            }
            else{ //if cell is dead.
                if(neighbors == 3){
                    this->grid[y][x] = true; //make alive!
                }
            }
        }
    }
}

bool Fungus::areValid(int y, int x){
    return( (y >= 0) && (y < 5) &&
            (x >= 0) && (x < 5));
}
