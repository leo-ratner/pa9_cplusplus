#include "renderer.h"
#include "ui_renderer.h"

#include <QDebug>

Renderer::Renderer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Renderer)
{
    ui->setupUi(this);
    colorMap = new ColorMap(); //setup color map. Only ever needs to be done once.
}

Renderer::~Renderer()
{
    delete ui;
    delete colorMap;
}

void Renderer::setGarden(Garden* garden){
    this->garden = garden;
}

void Renderer::paintEvent(QPaintEvent *event){
    QRect rect = event->rect(); //rect is used to find current screen size.

    QPainter painter(this); //the thing that actally does the drawing.

    painter.setRenderHint(QPainter::Antialiasing); //AA probably not needed, but whatever.

    //set the scale so that we have the proper number of divisions for our grid and stuff.
    //painter.scale(rect.width()/xDivs, rect.height()/yDivs);

    //painter.setBackground(Qt::black); //black BG by default.


    //ok, now we need to loop over the garden data.

    //fuck writing that vector thing again

    //create image to draw to.

    //MAKE SURE the garden isn't null. If it is, draw using default scale.


    //if the whole garden is null, just don't change anything.

    //remember, xDivs and yDivs have the x5 factor INCLUDED.
    //why did I do it that way? because I am dumb as hell, that is why.

    QImage frame(xDivs, yDivs, QImage::Format_RGB32);

    frame.fill(Qt::black);

    if(garden != nullptr){
        //qInfo() << "garden is not null!";
        //the garden object actually does the drawing logic.
        //don't forget to give it our color map!
        painter.drawImage(painter.viewport(), garden->writeToImage(this->colorMap));
    }else{
        //let's see if the new version works.
        frame.setPixelColor(1,1, Qt::blue);
        frame.setPixelColor(2,1, Qt::red);
        painter.drawImage(painter.viewport(), frame);
    }

    //huge-ass loop, draw to pixmap.
//    for(int row = 0; row < current.size(); row++){
//        for(int col = 0; col < current[row].size(); col++){

//            //do nothing if null.
//            if(current[row][col]!=nullptr){
//                //for debug purposes, right now let's just paint any filled in plot green.
//                for(int plotRow = 0; plotRow < 5; plotRow++){ //we know we have a static 5x5 array.
//                    for(int plotCol = 0; plotCol < 5; plotCol++){
//                    }
//                }
//            }
//        }
//    }

//    //for debugging purposes, let's draw a few pixels.
//    painter.setPen(Qt::blue);
//    painter.drawPoint(1,1);
//    painter.setPen(Qt::red);
//    painter.drawPoint(2,1);
}

void Renderer::setDivisions(int x, int y){
    xDivs = x;
    yDivs = y;
}
