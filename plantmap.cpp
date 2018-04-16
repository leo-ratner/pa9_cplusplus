#include "plantmap.h"

//this map also stores a bunch of colors and shit.

PlantMap::PlantMap()
{
    //ugh. Gotta populate the map.
    nameMap = new std::unordered_map<std::string, pdt::Ptype>();

    //just manually jam everything into the map. We'll only instantiate this once at startup,
    //so hopefully we won't have to worry about dealing with setting it up more than once.


    const std::array<std::string, 5> trees{{"OAK", "WILLOW", "BANANA", "COCONUT", "PINE"}} ;
    const std::array<std::string, 6> flowers{{"IRIS", "LILY", "ROSE", "DAISY", "TULIP", "SUNFLOWER"}};
    const std::array<std::string, 5> vegetables{{"GARLIC", "ZUCCHINI", "TOMATO", "YAM", "LETTUCE"}};

    //custom ones.
    const std::array<std::string, 5> fungi{{"LICHEN", "BASIDIOMYCOTA", "ASCOMYCOTA", "ALIEN"}};


    //c++ has wierd ranged for loops. Also auto is a strange thing.
    for(const auto& s: trees)
    {
        nameMap->emplace(s, pdt::TREE);
    }
    for(const auto& s: flowers)
    {
        nameMap->emplace(s, pdt::FLOWER);
    }
    for(const auto& s: vegetables)
    {
        nameMap->emplace(s, pdt::VEGETABLE);
    }
    for(const auto& s: fungi)
    {
        nameMap->emplace(s, pdt::FUNGUS);
    }




}

PlantMap::~PlantMap()
{
    delete nameMap;
    //delete colMap;
}


pdt::Ptype PlantMap::getType(std::string name)
{
    //unordered_map returns a k/v pair iterator type by default.
    if(nameMap->find(name) != nameMap->end())
    {
        return nameMap->find(name)->second; //get val from kv pair
    }
    return pdt::ERR;
}

