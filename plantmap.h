#ifndef PLANTMAP_H
#define PLANTMAP_H

#include "planttypes.h"
#include <unordered_map>
#include <string>
#include <array>

//used for the color maps.
//#include <QColor>
//#include <QHash> //TODO: port the type map to qstring and qmap.
//#include <QString>

class PlantMap
{
public:
    PlantMap();
    ~PlantMap();

    pdt::Ptype getType(std::string name);
    //QColor getColor(std::string name);

private:


    std::unordered_map<std::string, pdt::Ptype>* nameMap; //TODO: Populate the name map.
    //QHash<QString, QRgb>* colMap;
};

#endif // PLANTMAP_H
