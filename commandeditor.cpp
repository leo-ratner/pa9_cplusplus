#include "commandeditor.h"
#include "ui_commandeditor.h"

#include <QDebug>

CommandEditor::CommandEditor(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CommandEditor)
{
    ui->setupUi(this);
    this->valid = false; //assume invalid file on first startup.
    this->startPoint = 0; //initially, assume start at 0.
}

CommandEditor::~CommandEditor()
{
    delete ui;
}

void CommandEditor::on_actionNew_triggered()
{
    currentFile.clear(); //clear filename
    this->ui->textEdit->setPlainText(QString()); //wipe text editor
    this->ui->fileLabel->setText("No file specified. It is good practice to save your file."); //reset file label.
    goToFirstLine(); //make sure we're at line zero.
}



void CommandEditor::on_actionOpen_triggered()
{
    QString fName = QFileDialog::getOpenFileName(this, "Open command file");
    QFile file(fName); //attempt to create file. QT handles exceptions.
    currentFile = fName; //NOTE: possibly change type of currentText? qFile is a subclass but idk.

    //IO error checking.
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return; //have to re-open dialog to try again. Might change later.
    }
    //otherwise, update the open file label.
    this->ui->fileLabel->setText(fName);
    QTextStream in(&file); //stream to read text in from.
    QString text = in.readAll();

    //apply text to the textedit box. We're not going to store this internally,
    //instead we're gonna require the user to save the file before the sim will run,
    //I could do it the other way, but it's just good practice to enforce that.

    //important note: remember to write the code and not just the comment, jackass.
    ui->textEdit->setPlainText(text);

    file.close();//terminate read.

    //finally, remember to reset our line
    goToFirstLine();
}

void CommandEditor::on_actionSave_triggered()
{
    QString fName;
    //if no file name was defined, prompt for one.
    //TODO: just have this reroute to the "Save as" action.
    if(currentFile.isEmpty())
    {
        fName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fName;
    }else
    {
        fName = currentFile; //if file already exists.
    }
    QFile file(fName);
    //actually do the saving.
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    //update the file label
    this->ui->fileLabel->setText(fName);
    QTextStream out(&file);
    QString text = this->ui->textEdit->toPlainText(); //convert
    out << text; //write using C++ stream wierdness.
    file.close();
}

void CommandEditor::on_actionSaveAs_triggered()
{
    //TODO: Remove redundant code between this and the save action.
    //or maybe not, since this way we don't need to deal with as much heap storage.

    QString fName = QFileDialog::getSaveFileName(this, "Save As");
    QFile file(fName); //as I said above, we probably don't want these in heapspace, so idk...

    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
}

/*  wrappers for basic text editing features. */
void CommandEditor::on_actionCopy_triggered(){this->ui->textEdit->copy();}
void CommandEditor::on_actionPaste_triggered(){this->ui->textEdit->paste();}
void CommandEditor::on_actionCut_triggered(){this->ui->textEdit->cut();}
void CommandEditor::on_actionUndo_triggered(){this->ui->textEdit->undo();}
void CommandEditor::on_actionRedo_triggered(){this->ui->textEdit->redo();}



//new stuff which can get/set a line and stuff

//go to the line marked as "startPoint".
void CommandEditor::goToFirstLine()
{

    this->goToLine(startPoint);
}


//fixed version designed for the new command tracker.
//please note this program assumes the line it starts at IS NOT BLANK.
//if it is blank, it returns an empty string first time around.
QString CommandEditor::nextCommand()
{
    QTextCursor* tracker = this->ui->textEdit->lineTracker; //cursor copy

    QString cur = ""; //initially, current line is blank.
    QString out = tracker->block().text(); //current line is our output.

    //always move down at least once at the start.
    tracker->movePosition(QTextCursor::Down);

    //we then jump the cursor to the next non-blank line.

    //loop, break out if we hit a non-blank line
    while(!tracker->atEnd()){
        cur = tracker->block().text(); //find what our current text is.
        //if cur is no longer just whitespace, immediately break.
        if(cur != "" && !cur.trimmed().isEmpty()) break;
        tracker->movePosition(QTextCursor::Down);
    }


    this->ui->textEdit->updateView(); //emit step signal.


    qInfo() << out; //debug at the moment to print our current command.

    //this->ui->textEdit->setTextCursor(newLoc);
    return out; //return previous command.
}


//these do not track the text cursor, they track the *COMMAND* cursor.

void CommandEditor::goToLine(int line)
{
    //move cursor to line index.
    //QTextCursor newLoc = this->ui->textEdit->textCursor(); //cursor copy

    this->ui->textEdit->lineTracker->setPosition(line);
    this->ui->textEdit->updateView(); //MUST be called so we update the display
//    newLoc.setPosition(line);
//    this->ui->textEdit->setTextCursor(newLoc);

}

bool CommandEditor::atEnd()
{
    return this->ui->textEdit->lineTracker->atEnd();
}

bool CommandEditor::isValid()
{
    return this->valid;
}

//this function attempts to scan over the current document and determine stuff like garden width, height, etc.
//if it cannot do so, we mark a the "INVALID" flag, and set the current garden object to null.
//IMPORTANT NOTE: Calling this DELETES the existing garden!
Garden* CommandEditor::attemptGardenSetup(double& del)
{
    //delete garden;

    //create a new cursor to loop over the doc.
    QTextCursor cur(this->ui->textEdit->document()); //store on stack, we only need it once.
    cur.setPosition(0); //set position to start.


    qInfo() << "Running garden setup...";

    //do some quick sanity tests to auto-fail the attempt if conditions aren't met.
    if(this->ui->textEdit->blockCount() < 3){ valid = false; return nullptr;} //if we don't have a large enough file.
    qInfo() << "Size check OK";
    //now try and loop the cursor through stuff, the format should be something like
    /*
      rows: [int]
      cols: [int]
      delay: [float]
    */
    //specifically in that order. We do get to loop over and ignore whitespace lines.

    //call this 3 times, check valid formatting.

    //for now this is gonna have some redundant code.
    //TODO: Refactor this, it is an utter mess right now.

    int row, col;
    double delay;

    QStringList coms;

    bool ok; //used to check if conversion operation worked.


    //get first non-blank line.
    nextNonEmpty(cur);

    //check row formatting
    coms = cur.block().text().trimmed().toUpper().split(" "); //split by whitespace. ugly call chain
    if(coms.length() < 2 || coms[0] != "ROWS:") {valid = false; return nullptr;} //make sure length is correct.
    row = coms[1].toInt(&ok); if(!ok){ valid = false; return nullptr;}//do operation, return if failure.
    qInfo() << "row check OK";

    cur.movePosition(QTextCursor::Down); //always go down at LEAST one line.


    //check column formatting
    nextNonEmpty(cur);
    coms = cur.block().text().trimmed().toUpper().split(" ");
    if(coms.length() < 2 || coms[0] != "COLS:") {valid = false; return nullptr;}
    col = coms[1].toInt(&ok); if(!ok){ valid = false; return nullptr;}
    qInfo() << "col check OK";

    cur.movePosition(QTextCursor::Down); //always go down at LEAST one line.

    nextNonEmpty(cur);
    coms = cur.block().text().trimmed().toUpper().split(" ");
    if(coms.length() < 2 || coms[0] != "DELAY:") {valid = false; return nullptr;}
    delay = coms[1].toDouble(&ok); if(!ok) {valid = false; return nullptr;}
    qInfo() << "delay check OK";

    //attempt to instantiate object.

    del = delay; //set delay value reference.

    cur.movePosition(QTextCursor::Down); //always go down at LEAST one line.

    //set start point to next valid line, or the current one if we're at the end. Though hopefully that won't happen.
    nextNonEmpty(cur);

    startPoint = cur.position();

    this->goToLine(startPoint);

    qInfo() << "setup succeeded.";

    return new Garden(row, col); //this should work now.

}


//helper function, used to jump to next valid line.N

//NOTE: not 100% sure referencing in this way will work. We may have to change this.
void CommandEditor::nextNonEmpty(QTextCursor &cur)
{
    //int offset = cur.position();

    while(!cur.atEnd()){
        if(!cur.block().text().trimmed().isEmpty()) break;
        //offset++;
        cur.movePosition(QTextCursor::Down); //attempt to move down.
    }
    //qInfo() << offset;
    //return offset;
}

int CommandEditor::getStartPoint(){
    return this->startPoint;
}

int CommandEditor::getCurrentLine(){
    return this->ui->textEdit->lineTracker->blockNumber() +1; //get line number.
    //add one because of stupid stuff.
}

int CommandEditor::getLineCount(){
    return this->ui->textEdit->blockCount();
}
