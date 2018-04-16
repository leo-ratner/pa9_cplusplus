#ifndef COLORMAP_H
#define COLORMAP_H

#include <string>
#include <QColor>
#include <QHash>
#include <QString>
#include <QRgb>


class ColorMap
{
public:
    ColorMap();
    ~ColorMap(){delete colMap;}

    QColor getColor(std::string name);

private:
    QHash<QString, QRgb>* colMap;
};

#endif // COLORMAP_H
