#include "commandtextedit.h"

#include <QtWidgets>

CommandTextEdit::CommandTextEdit(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this); //create the area that shows the numbers n' stuff.

    lineTracker = new QTextCursor(document()); //create tracking cursor.

    //always start at line zero.

    lineTracker->setPosition(0);
    //connect signals/slots in code because we don't have a form for this.
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));

    //todo: change this one or update cursor position to indicate currently running line when sim is running
    connect(this, SIGNAL(commandStep()), this, SLOT(highlightCurrentCommandLine()));
    connect(this, SIGNAL(textChanged()), this, SLOT(highlightCurrentCommandLine()));
    //connect(this, SIGNAL(update()), this, SLOT(highlightCurrentCommandLine()));


    updateLineNumberAreaWidth(0); //0 default. has no effect atm.
    //highlightCurrentLine();
    highlightCurrentCommandLine();
}

CommandTextEdit::~CommandTextEdit()
{
    delete lineNumberArea;
    delete lineTracker;
}

int CommandTextEdit::lineNumberAreaWidth()
{
    //compute the area size we want for the line numbers.

    //first step, determine the max number of digits we want to have, depending on how many lines.
    //(We don't want stuff like 001 if we only have 9 lines, for example.
    int digits = 1;
    int max = qMax(1, blockCount());
    while(max>=10){
        //add digit every tens.
        max /= 10;
        digits++;
    }


    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits; //set width based on char size.

    return space;
}

void CommandTextEdit::updateLineNumberAreaWidth(int /*newblockcount*/)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0); //add view offset to allow for the numbering bits.
}

//called when window resized, etc etc.
void CommandTextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
    if(dy)
    {
        lineNumberArea->scroll(0, dy); //when we scroll down, we scroll the numbers as well.
    }
    else
    {
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    }

    if(rect.contains(viewport()->rect())){
        updateLineNumberAreaWidth(0);
    }
}

void CommandTextEdit::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event); //invoke parent method

    //update the line numbering thingy.
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CommandTextEdit::highlightCurrentCommandLine()
{

    QList<QTextEdit::ExtraSelection> extraSelections;

    if(!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);

        //so how tf do we do this.

        //ensure we only select the current line.
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = *lineTracker; //will this work? Is this even a good idea? Who cares?
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);

}

void CommandTextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea); //setup painter in the line number area

    painter.fillRect(event->rect(), Qt::lightGray); //fill in area with light grey.

    QTextBlock block = firstVisibleBlock(); //first visible line in the editor
    int blockNumber = block.blockNumber(); //get our first line number.

    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();

    int bottom = top + (int) blockBoundingRect(block).height();

    //loop through visible lines and add line numbers.
    while(block.isValid() && top <= event->rect().bottom())
    {
        if(block.isVisible() && bottom >= event->rect().top())
        {
            QString lineNumber = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, lineNumber);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        blockNumber++;
    }
}

void CommandTextEdit::updateView()
{
    emit(commandStep()); //on step event emit our signal.
}
