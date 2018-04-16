#include "colormap.h"

ColorMap::ColorMap()
{


    //note to captain dingus: remember to actually INSTANTIATE
    //THE OBJECT. BLERGH.
    this->colMap = new QHash<QString, QRgb>();

    //FLOWERS!
    colMap->insert("IRIS", qRgb(190, 65, 244));
    colMap->insert("LILY", qRgb(238, 215, 239));
    colMap->insert("ROSE", qRgb(255, 0, 0));
    colMap->insert("DAISY", qRgb(229, 217, 80));
    colMap->insert("TULIP", qRgb(183, 86, 147));
    colMap->insert("SUNFLOWER", qRgb(255, 182, 0));

    //TREES!
    colMap->insert("OAK", qRgb(0, 135, 24));
    colMap->insert("WILLOW", qRgb(78, 158, 12));
    colMap->insert("BANANA", qRgb(188, 221, 0));
    colMap->insert("COCONUT", qRgb(181, 119, 57));
    colMap->insert("PINE", qRgb(0, 102, 40));

    //VEGETABLES!
    colMap->insert("GARLIC", qRgb(220, 224, 204));
    colMap->insert("ZUCCHINI", qRgb(32, 68, 45));
    colMap->insert("TOMATO", qRgb(255, 80, 0));
    colMap->insert("YAM", qRgb(255, 166, 71));
    colMap->insert("LETTUCE", qRgb(101, 191, 76));

    //FUNGI!

    colMap->insert("LICHEN", qRgb(142, 163, 101));
    colMap->insert("BASIDIOMYCOTA", qRgb(123, 0, 255));
    colMap->insert("ASCOMYCOTA", qRgb(142, 163, 101));
    colMap->insert("ALIEN", qRgb(95, 136, 239));
}

QColor ColorMap::getColor(std::string name)
{
        //find color, if it's not there set to some default color.

        QString key = QString::fromStdString(name); //compatability.

        QRgb col = this->colMap->value(key, qRgb(117,117,117)); //defaults to grey

        return QColor(col);
}
