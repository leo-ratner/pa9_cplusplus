#ifndef RENDERER_H
#define RENDERER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include "garden.h"


namespace Ui {
class Renderer;
}

class Renderer : public QWidget
{
    Q_OBJECT

public:
    explicit Renderer(QWidget *parent = 0);
    ~Renderer();

    void paintEvent(QPaintEvent *event) override;

    void setDivisions(int x, int y);

    void drawGarden();

    void setGarden(Garden*);

private:
    Ui::Renderer *ui;

    int xDivs;
    int yDivs;

    Garden* garden;
    ColorMap* colorMap;

};

#endif // RENDERER_H
