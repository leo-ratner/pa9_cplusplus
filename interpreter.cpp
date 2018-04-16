#include "interpreter.h"
#include <QDebug>


//callback wierdness you don't want to know about.
void funcRemove(Plant* pl, Garden* g, int row, int col){g->removeAt(col,row);} //calling delete in a callback? What could possibly go wrong? :P
void funcGrow(Plant* pl, Garden* g, int row, int col){pl->grow();}

Interpreter::Interpreter(Garden *garden)
{
    this->garden = garden;
    this->pMap = new PlantMap();
}

Interpreter::~Interpreter()
{
    delete pMap;
}


void Interpreter::evaluate(QString line)
{
    QStringList coms = line.toUpper().trimmed().split(" ");
    if(coms.size() == 0)
    {
        return;
        //if somehow a blank line gets in there.
    }

    //c++ switches only work with ints because argh

    QString c = coms.at(0);

    if(c == "PLANT") doPlant(coms);
    if(c == "GROW") doGrow(coms);
    if(c == "HARVEST") doRemove(coms, pdt::VEGETABLE);
    if(c == "PICK") doRemove(coms, pdt::FLOWER);
    if(c == "CUT") doRemove(coms, pdt::TREE);
    if(c == "REMOVE") doRemove(coms, pdt::FUNGUS);

    //if none of the commands work, we'll just skip over the line and not do anything.
    //TODO: somehow indicate that the current line has an error of some sort.
}

void Interpreter::doPlant(QStringList com)
{
    qInfo() << "PLANTING...";
    if(com.size() == 3) //ensure command is well-formed.
    {
        qInfo() << "Correct size.";
        qInfo() << com.at(1);
        if(com.at(1).contains(QRegularExpression("[(]\\d+[,]\\d+[)]"))){
            qInfo() << "Well-formed";
            QStringList pts = com[1].replace(QRegularExpression("[()]|\\s+"), "").split(",");

            std::string plantName = com[2].toUpper().trimmed().toStdString();
            //just immediately plant at the correct point in the garden.

            //check if points are even in range

            int x = pts[0].toInt();
            int y = pts[1].toInt();

            if(x < 0 || x >= garden->getCols() || y < 0 || y >= garden->getRows())
                return; //just terminate.

            Plant* plant;

            //determine plant type.
            switch(pMap->getType(plantName))
            {
            case pdt::FLOWER:
                plant = new Flower(plantName);
                qInfo() << "FLOWER";
                break;
            case pdt::TREE:
                plant = new Tree(plantName);
                break;
            case pdt::VEGETABLE:
                plant = new Vegetable(plantName);
                break;
            case pdt::FUNGUS:
                plant = new Fungus(plantName);
                break;
            default:
                qInfo() << "INVALID NAME";
                plant = nullptr;
            }

            qInfo() << (garden == nullptr); //this shouldn't even be possible what the ACTUAL FUCK
            //if the spot is empty...
            if(garden->getPlantAt(pts[0].toInt(), pts[1].toInt()) == nullptr)
            {
                garden->plantAt(plant, pts[0].toInt(), pts[1].toInt());
            }

        }
    }
}

void Interpreter::doGrow(QStringList com)
{

    int steps;
    if(com.size() == 2)
    {
        //simplest version, call grow on *all* plants
        qInfo() << "Growing All.";
        steps = com.at(1).simplified().toInt();
        qInfo() << "Steps:" << steps;

        //literally just loop and manually grow if not null
        garden->loopAndCallOnValid(pMap, funcGrow, steps, "");
    }
    if(com.size() == 3)
    {
        qInfo() << "GROWING at specified point!";
        //check if we're growing a specific point.
        if(com.at(2).contains(QRegularExpression("[(]\\d+[,]\\d+[)]")))
        {
            QStringList pts = com[2].replace(QRegularExpression("[()]|\\s+"), "").split(",");
                    //split into coordinates.
            Plant *plant = garden->getPlantAt(pts.at(0).toInt(), pts.at(1).toInt());

            steps = com.at(1).simplified().toInt();
            qInfo() << "Steps:" << steps;

            if (plant != nullptr){
                //if not null, loop and grow. The loop is so it can grow more than once if it needs to.
                for(int i = 0; i < steps; i++)
                {
                    plant->grow(); //just call grow directly on our ref.
                }
            }
        }

        else //if not point format, we have a type or name.
        {
            steps = com.at(1).simplified().toInt();
            //otherwise, we assume we gave a plant name or plant type. This makes things easier.
            QString nameOrType = com.at(2).simplified();
            garden->loopAndCallOnValid(pMap, funcGrow, steps, nameOrType.toStdString());
        }
    }

    //if those all fail, we have a malformed command. Just ignore it.
}

void Interpreter::doRemove(QStringList com, pdt::Ptype type)
{
    std::string typeString = "INVALID NAME";

    //convert ptype enum to string.
    //initially set to something that will never return any results, so that even if it somehow misses the
    //check it won't remove things
    switch(type)
    {
    case pdt::TREE: typeString = "TREE"; break;
    case pdt::FLOWER: typeString = "FLOWER"; break;
    case pdt::FUNGUS: typeString = "FUNGUS"; break;
    case pdt::VEGETABLE: typeString = "VEGETABLE"; break;
    }

    if(typeString == "INVALID NAME")
    {
        return; //terminate if we don't have a correct type name.
    }

    if (com.size() == 1) //remove all of specified type. Simplest case.
    {
        garden->loopAndCallOnValid(pMap, funcRemove, 1, typeString);
    }
    else if(com.size() == 2) //everything else.
    {
        //check if we've got a command formatted as a point.
        if(com.at(1).contains(QRegularExpression("[(]\\d+[,]\\d+[)]")))
        {

            QStringList pts = com[1].replace(QRegularExpression("[()]|\\s+"), "").split(","); //get our points, and the plant at that point.

            int x = pts.at(0).toInt();
            int y = pts.at(1).toInt();

            Plant* target = garden->getPlantAt(x, y);

            //if correct type, and not a nullptr
            if(target !=  nullptr && target->type() == type)
            {
                qInfo() << "Removing point";
                garden->removeAt(x,y);
            }


        }
        else{ //otherwise, we've specified a name.
            pdt::Ptype typeFromName = this->pMap->getType(com[1].toUpper().trimmed().toStdString());

            if(typeFromName == type)
            {
                garden->loopAndCallOnValid(pMap, funcRemove, 1, com[1].toUpper().trimmed().toStdString()); //remove all with name.
            }

        }
    }
}

void Interpreter::setGarden(Garden* garden)
{
    this->garden = garden;
}

