#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSettings>
#include "interpreter.h"

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

    void on_actionSave_As_triggered();

    void on_actionOpen_triggered();

    void on_pushButton_2_clicked();

    void on_StepButton_clicked();

    void on_ResetButton_clicked();


private slots:

    void doSimStep();

private:
    Ui::MainWindow *ui;

private:
    //garden-related private vars.
    Garden *garden;
    double delay;
    QTimer *timer;

    Interpreter *interpreter;
};

#endif // MAINWINDOW_H
