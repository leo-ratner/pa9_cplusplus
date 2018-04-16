#ifndef COMMANDTEXTEDIT_H
#define COMMANDTEXTEDIT_H

#include <QPlainTextEdit>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea; //to be defined later.

class CommandTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit CommandTextEdit(QWidget *parent = 0);
    ~CommandTextEdit();

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    QTextCursor *lineTracker; //screw memory safety! :/

signals:
    //I have no idea how to use these.
    void commandStep();

public slots:
    void updateView();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    //void highlightCurrentLine();
    void updateLineNumberArea(const QRect&, int);

    void highlightCurrentCommandLine(); //this doesn't use the cursor, it tracks using the currentLine data.

private:
    QWidget *lineNumberArea;
    int currentLineStep;

    //second cursor, this one is used to track what line we are currently on.
};


class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CommandTextEdit *editor) : QWidget(editor){
        commandEditor = editor;
    }

    QSize sizeHint() const override{
        return QSize(commandEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        commandEditor->lineNumberAreaPaintEvent(event);
    }
private:
    CommandTextEdit *commandEditor;
};

#endif // COMMANDTEXTEDIT_H
