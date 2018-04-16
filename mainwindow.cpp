#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->isRunning = false; //pause simulation by default.

    this->isReady = false; //by default we haven't set things up yet.

    this->delay = 0.1f; //default delay value.

    //initially, garden and interpreter are both null. We reinitialize both of them later.
    this->garden = nullptr;
    this->interpreter = new Interpreter(garden);

    ui->renderView->setGarden(this->garden);
    //make sure we set our render area to some default scale.

    ui->renderView->setDivisions(40,40);
    ui->renderView->update();

    //create the timer we're gonna use to loop through all the commands.
    //set it to our default delay value, which is 0.1.
    this->timer = new QTimer(this);
    timer->setInterval((int)(this->delay*1000)); //interval is in milliseconds.

    //link the timer to the step command.
    connect(this->timer, SIGNAL(timeout()), this, SLOT(doSimStep()));

    //resize our window so it's not so friggin tiny.
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    //connect all our crap
    connect(ui->actionUndo, SIGNAL(triggered()), ui->editor, SLOT(on_actionUndo_triggered()));
    connect(ui->actionRedo, SIGNAL(triggered()), ui->editor, SLOT(on_actionRedo_triggered()));
    connect(ui->actionCut, SIGNAL(triggered()), ui->editor, SLOT(on_actionCut_triggered()));
    connect(ui->actionCopy, SIGNAL(triggered()), ui->editor, SLOT(on_actionCopy_triggered()));
    connect(ui->actionPaste, SIGNAL(triggered()), ui->editor, SLOT(on_actionPaste_triggered()));

    //finally, create settings and stuff.
}

MainWindow::~MainWindow()
{
    delete ui;
    delete garden;
}


//commands call the actions of the child object.
void MainWindow::on_actionNew_triggered()
{
    this->ui->editor->make_new();
}

void MainWindow::on_actionSave_triggered()
{
    this->ui->editor->save();
}

void MainWindow::on_actionSave_As_triggered()
{
    this->ui->editor->saveAs();
}

void MainWindow::on_actionOpen_triggered()
{
    this->ui->editor->open();
}


//actual simulation commands

void MainWindow::on_pushButton_2_clicked()
{

    //if we're at the end when we click start, just call a reset.
    //this also runs if the simulation isn't marked as ready to go, in which case
    //we try and get it ready.
    if(this->currentSimStep >= this->ui->editor->getCurrentLine()){
        this->on_ResetButton_clicked(); //call reset if we've hit the last line.
    }

    if(!(this->isReady))
    {
        this->on_ResetButton_clicked(); //reset
        return; //don't even attempt to run the simulation.
    }

    //this->ui->editor->goToLine(this->currentSimStep); //move cursor back to current step.

    if(this->isRunning)
    {
        //stop the timer if it was running.
        this->timer->stop();

        this->isRunning = false;
        this->ui->pushButton_2->setText("START SIMULATION");
    }
    else
    {
        //restart the timer
        this->timer->start((int)(this->delay*1000));

        //this->ui->editor->goToLine(this->currentSimStep);
        this->isRunning = true;
        this->ui->pushButton_2->setText("STOP SIMULATION");
    }
    //make sure the step and reset buttons can't be pressed while the sim is running.
    this->ui->StepButton->setEnabled(!isRunning);
    this->ui->ResetButton->setEnabled(!isRunning);
}

void MainWindow::on_StepButton_clicked()
{
    //TESTING FOR NOW ONLY, let's see if we can use this to increment the line or do something similar...

    //only step if simulation is ready.
    if(this->isReady /*&& this->currentSimStep != this->ui->editor->getLineCount()*/)
    doSimStep();
}

void MainWindow::on_ResetButton_clicked()
{
    //attempt to generate new garden. Seems to work ok!
    qInfo() << "RUNNING RESET";

    //delete old garden and rebuild it.
    delete garden;
    this->garden = this->ui->editor->attemptGardenSetup(delay);
    this->currentSimStep = this->ui->editor->getStartPoint(); //set sim step to start point.

    this->ui->editor->goToFirstLine(); //reset cursor position

    //if the garden successfully generated, set up the new view scale, and create
    //the interpreter. Also, mark the sim as ready to go.
    if(garden != nullptr){
        ui->renderView->setDivisions(5*garden->getRows(),5*garden->getCols());
        ui->renderView->update();

        this->isReady = true; //sim is good to go!
    }else{
        this->isReady = false;
    }

    //qInfo() << "Delay: " << this->delay;
    ui->renderView->setGarden(this->garden);
    ui->renderView->update();

}

void MainWindow::doSimStep()
{
    //get current line number
    this->currentSimStep = this->ui->editor->getCurrentLine();
    //also checks and stops the sim at the end.
    qInfo() << this->currentSimStep << "/" << this->ui->editor->getLineCount();

    QString line = this->ui->editor->nextCommand(); //step to next command.


    if (this->garden != nullptr){

        //TODO: FIGURE OUT WHY THE FUCK the interpeter gets
        //the garden as a null pointer BUT ALSO RUNS IT HOW IN THE SHIT
        interpreter->setGarden(this->garden);
        interpreter->evaluate(line); //evaluate our line.
    }

    ui->renderView->setGarden(this->garden);
    ui->renderView->update();

    //if we hit the end, just freeze it.
    if(this->currentSimStep == this->ui->editor->getLineCount())
    {
            this->timer->stop();
            this->isRunning = false;
            this->ui->pushButton_2->setText("START SIMULATION");
            this->ui->StepButton->setEnabled(!isRunning);
            this->ui->ResetButton->setEnabled(!isRunning);
    }

}
