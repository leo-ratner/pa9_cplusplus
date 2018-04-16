#include "garden.h"

#include <QDebug>

Garden::Garden(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;

    //setup grid. Holy fucking shit.
    this->grid = std::vector<std::vector<Plant*>>(this->rows, std::vector<Plant*>(this->cols));

    //presumably this creates an array of nullptrs? God I hope so...

    //print out rows and cols to see if this works
    qInfo() << "garden rows: " << this->rows;
    qInfo() << "garden cols: " << this->cols;


    //have to manually setup rows to fill with
    this->grid.resize(this->rows);
    for(int i = 0; i < this->rows; i++)
    {
        this->grid[i].resize(this->cols, nullptr);
    }

}

Garden::~Garden()
{
    for(int y = 0; y < rows; y++)
    {
        for(int x = 0; x < cols; x++)
        {
            delete grid[y][x];
        }
    }
    //grid.clear();
}

void Garden::plantAt(Plant* plant, int x, int y)
{
    grid[y][x] = plant;
}

void Garden::growAt(int x, int y){
    if(grid[y][x] != nullptr){
        grid[y][x]->grow();
    }
}

void Garden::removeAt(int x, int y){
    delete grid[y][x];
    grid[y][x] = nullptr; //for some reason, have to manually reset pointer.
    //what the fuck? why does this ONLY work on point 0,0?
}

Plant* Garden::getPlantAt(int x, int y)
{
    return this->grid[y][x];
}

//takes name/type, loops over all plants and runs callback if the conditions match.
void Garden::loopAndCallOnValid(PlantMap* pMap, callback_function func, int steps, std::string name)
{
    qInfo() << "running loop";
    pdt::Ptype ctype = pdt::ERR; //type is ERR by default. This way we know it's unsassigned!
    bool testNameFlag; //whether or not we have a name or a type!

    //test if it's one of the types
    if(name == "TREE" || name == "FLOWER" || name == "VEGETABLE" || name=="FUNGUS" || name == "")
    {
        //no reflection, so manually test *again* to set proper enum type.
        if(name == "TREE") ctype = pdt::TREE;
        if (name == "FLOWER") ctype = pdt::FLOWER;
        if(name == "VEGETABLE") ctype = pdt::VEGETABLE;
        if (name == "FUNGUS") ctype = pdt::FUNGUS;
        testNameFlag = false; //only test plant type.
        //if something didn't get assigned here, we will crash with a memory access violation! :D
    } //gotta make sure the name isn't blak.
    else //otherwise, we have a name, not a type. We'll still need to check type, so get that with a map.
    {
        ctype = pMap->getType(name); //dont forget to convert string types.
        testNameFlag = true;
    }

    //now loop over everything, with very slightly different behavior depending on whether or not we have a
    //name or a type.

    //IMPORTANT NOTE: if an empty string is passed (the defualt condition), we assume we want to loop over *every*
    //node, regardless of name or type.

    for(int row = 0; row < grid.size(); row++)
    {
        for(int col = 0; col < grid[row].size(); col++)
        {
            //first, make sure point isn't empty.
            if(grid[row][col] != nullptr)
            {
                Plant* cur = grid[row][col]; //keep track of our current cell

                //check if the string is empty, or the type matches.
                if(name == "" || cur->type() == ctype)
                {
                    //behaviour here now depends on whether or not we want to test a name.
                    //if we do, we need one more validity check.
                    //at this point, we also do the functions however many times the steps variable specifies.

                    for(int i = 0; i < steps; i++)
                    {
                        if(testNameFlag)
                        {
                            if(cur->getName() == name){
                                func(cur, this, row, col); //call whatever our callback is.
                            }
                        }
                        else
                        {
                            func(cur, this, row, col); //run callback.
                        }
                    }
                }
            }
        }
    }

}
//gettors
int Garden::getRows()
{
    return this->rows;
}

int Garden::getCols()
{
    return this->cols;
}

//fuck it, we'll just write it to an image in here.
QImage Garden::writeToImage(ColorMap* colMap)
{
    //for now, just return flat red image as debug.
    QImage img(this->cols*5, this->rows*5, QImage::Format_RGB32);
    img.fill(Qt::black);
    //qInfo() << "row:" << rows << "col" << cols;
    //ok. Image creation is working. Now let's loop.

    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            //qInfo() << grid[y][x];
            //first, test if current plot is null
            if(grid[y][x] != nullptr){
                //bool currentGrid[5][5];

                //grid[y][x]->copyGridIntoOther(currentGrid);

                for(int i = 0; i < 5; i++){
                    for(int j = 0; j < 5; j++){
                        //if the grid isn't null, make sure the background is a brown color.
                        img.setPixelColor(x*5+j, y*5+i, QColor(86, 83, 80));
                        //need another nullptr check here.
                        if (grid[y][x]->getGrid()[j][i] == true){ //I HOPE THIS WORKS DAMMIT

                            QColor col = colMap->getColor(grid[y][x]->getName()); //get color.

                            img.setPixelColor(x*5+j, y*5+i, col);
                        }
                    }
                }
            }
            //DEBUG WHICH DISPLAYS NUMBER OF DIVISIONS.
            //img.setPixelColor(x*5, y*5, Qt::red);
        }
    }


    return img;
}
