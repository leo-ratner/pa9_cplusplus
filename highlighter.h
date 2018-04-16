#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QRegularExpression>
#include <QRegularExpressionMatch>


//this is gonna be slightly different in style then most of the other code, as it is directly adapted
//from the qt documentation's reccomendations on how to subclass the syntax highlihgter.
//(so for example using stuff like QVector insteaed of std::vector)
class Highlighter : public QSyntaxHighlighter
{

    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override; //actually does the coloring and stuff.

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> HighlightingRules; //list of rules.

//    QRegularExpression commentStartExpression;
//    QRegularExpression commentEndExpression;

    QTextCharFormat sizingFormat; //for "rows" and "cols"
    QTextCharFormat delayFormat; //for the "delay" command
    QTextCharFormat coordFormat; //for coordinates, eg: (0,1) type things/
    QTextCharFormat commentFormat; //comments, duh.
    QTextCharFormat plantFormat; //plant op
    QTextCharFormat growFormat; //grow op
    QTextCharFormat removeFormat; //remove op
    QTextCharFormat numFormat; //for single numerals.
    QTextCharFormat nameFormat; //all the plant names.
    QTextCharFormat typeFormat; //plant types.

};

#endif // HIGHLIGHTER_H
