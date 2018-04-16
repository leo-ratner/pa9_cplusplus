#ifndef COMMANDEDITOR_H
#define COMMANDEDITOR_H

#include <QFrame>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTextCursor>
#include <QTextBlock>
#include "garden.h"

/*
 * Note: This part of the code is mostly just based off of the example text editor tutorial
 * provided in the QT tutorial. As such, it has a higher degree of redundant code than the rest of
 * the program. This may be changed some time in the future, in which case hopefully I'll
 * remember to remove this comment.
*/

namespace Ui {
class CommandEditor;
}

class CommandEditor : public QFrame
{
    Q_OBJECT

public:
    explicit CommandEditor(QWidget *parent = 0);
    ~CommandEditor();



public slots:
    //little hack to keep actions private but invoke them from parent.
    //TODO: figure out if inline will speed this up.
    void make_new() {on_actionNew_triggered();}
    void open() {on_actionOpen_triggered();}
    void save() {on_actionSave_triggered();}
    void saveAs() {on_actionSaveAs_triggered();}


    //note: had to be made public to connect them in the parent widget.
public slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionCopy_triggered();

    void on_actionRedo_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

private:
    Ui::CommandEditor *ui;

    QString currentFile; //stores the current file name.

    bool valid;

    void nextNonEmpty(QTextCursor&);

    int startPoint; //where does the setup stop?

public slots:
    //stuff related to line number manipulation.
    void goToFirstLine();
    QString nextCommand(); //note, this *IGNORES* lines which are entirely whitespace.
    bool atEnd();
    void goToLine(int);
    bool isValid();

    Garden* attemptGardenSetup(double&);

    int getStartPoint();
    int getCurrentLine();
    int getLineCount();


//public slots:
//    void reset();
//    void stepOnce();
//    void loopThrough(bool);

};

#endif // COMMANDEDITOR_H
