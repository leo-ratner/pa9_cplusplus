#ifndef GARDEN_H
#define GARDEN_H

#include <vector>
#include <iterator>
#include "plant.h"
#include "plantmap.h"
#include "colormap.h"
#include <QImage>

#include "tree.h"
#include "vegetable.h"
#include "flower.h"
#include "fungus.h"

class Garden;

typedef void (*callback_function)(Plant*, Garden*, int, int); //at this point? Don't even ask.

class Garden
{
public:
    Garden(int,int);
    ~Garden();

    void plantAt(Plant* plant, int x, int y);

    //void growAll();
    //void growLoop(std::string s, bool isName);
    Plant* getPlantAt(int x, int y); //pls no change plant pointers
    void growAt(int x, int y);

    void loopAndCallOnValid(PlantMap*, callback_function, int steps = 1, std::string name = "");

    int getRows();
    int getCols();

    QImage writeToImage(ColorMap*);

    void removeAt(int x, int y);
private:


private:
    std::vector<std::vector<Plant*>> grid; //dynamic array of plant objects.
    //sort of insane pointer structure, so, yeah...

    //used to keep track of the number of rows and columns, since our
    //array doesn't have a set size.
    int rows = 0;
    int cols = 0;

};

#endif // GARDEN_H
