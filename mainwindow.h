#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSettings>
#include "interpreter.h"
#include "aboutdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //sim state variables
    bool isRunning;
    bool isReady;
    int currentSimStep = 0;

private slots:
    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionOpen_triggered();

    void on_pushButton_2_clicked();

    void on_StepButton_clicked();

    void on_ResetButton_clicked();


private slots:

    void doSimStep();

    //void on_actionAbout_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;

    AboutDialog* about; //about window.

private:
    //garden-related private vars.
    Garden *garden;
    double delay;
    QTimer *timer;

    Interpreter *interpreter;
};

#endif // MAINWINDOW_H
