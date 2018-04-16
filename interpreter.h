#ifndef INTERPRETER_H
#define INTERPRETER_H


#include "garden.h"
#include "renderer.h"
#include <QTextStream>
#include <QThread>
#include <QRegularExpression>
#include <QtWidgets>



//reads in commands and calls functions on a garden object.

class Interpreter
{
public:
    Interpreter(Garden *garden);
    ~Interpreter();

    void evaluate(QString line);

    void setGarden(Garden*);

   // void parse2(QTextDocument, Renderer*); //improved version of parse that reads/updates internal data.


private:

    void doGrow(QStringList);
    void doPlant(QStringList);
    void doRemove(QStringList, pdt::Ptype);

    Garden *garden; //ref to current garden
    PlantMap *pMap;
};

#endif // INTERPRETER_H
