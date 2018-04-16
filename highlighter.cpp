#include "highlighter.h"

Highlighter::Highlighter(QTextDocument* parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    //setup all our highlighting rules.

    sizingFormat.setForeground(Qt::darkCyan);
    sizingFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("\\brows:|\\bcols:", QRegularExpression::CaseInsensitiveOption);
    rule.format = sizingFormat;
    HighlightingRules.append(rule);

    delayFormat.setForeground(Qt::darkMagenta);
    delayFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("\\bdelay:", QRegularExpression::CaseInsensitiveOption);
    rule.format = delayFormat;
    HighlightingRules.append(rule);

    coordFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression("[(]\\d+[,]\\d+[)]");
    rule.format = coordFormat;
    HighlightingRules.append(rule);

    commentFormat.setForeground(Qt::gray);
    commentFormat.setFontItalic(true);
    rule.pattern = QRegularExpression("^\\%[^\n]*");
    rule.format = commentFormat;
    HighlightingRules.append(rule);

    plantFormat.setForeground(Qt::darkBlue);
    plantFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("plant", QRegularExpression::CaseInsensitiveOption);
    rule.format = plantFormat;
    HighlightingRules.append(rule);

    growFormat.setForeground(Qt::darkGreen);
    growFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("grow", QRegularExpression::CaseInsensitiveOption);
    rule.format = growFormat;
    HighlightingRules.append(rule);

    removeFormat.setForeground(Qt::darkRed);
    removeFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("\\bremove\\b|\\bcut\\b|\\bpick\\b|\\bharvest\\b", QRegularExpression::CaseInsensitiveOption);
    rule.format = removeFormat;
    HighlightingRules.append(rule);

    numFormat.setForeground(QColor(127, 113, 82));
    rule.pattern = QRegularExpression("\\b\\d+\\b", QRegularExpression::CaseInsensitiveOption);
    rule.format = numFormat;
    HighlightingRules.append(rule);

    nameFormat.setForeground(QColor(4, 84, 30));
    nameFormat.setFontItalic(true);
    //doing this with a loop because otherwise it would be a massive pain. Not that this wasn't.
    QStringList namePatterns;
    namePatterns << "\\boak\\b" << "\\bwillow\\b" << "\\bbanana\\b" << "\\bcoconut\\b" << "\\bpine\\b"
                 << "\\biris\\b" << "\\blily\\b" << "\\brose\\b" << "\\bdaisy\\b" << "\\btulip\\b" << "\\bsunflower\\b"
                 << "\\bgarlic\\b" << "\\bzucchini\\b" << "\\btomato\\b" << "\\byam\\b" << "\\blettuce\\b"
                 << "\\blichen\\b" << "\\bbasidiomycota\\b" << "\\bascomycota\\b" << "\\balien\\b";

    foreach(const QString &pattern, namePatterns)
    {
        rule.pattern = QRegularExpression(pattern, QRegularExpression::CaseInsensitiveOption);
        rule.format = nameFormat;
        HighlightingRules.append(rule);
    }

    typeFormat.setForeground(QColor(30, 81, 76));
    typeFormat.setFontWeight(QFont::Bold);
    typeFormat.setFontItalic(true);
    rule.pattern = QRegularExpression("\\bflower\\b|\\bvegetable\\b|\\btree\\b|\\bfungus\\b", QRegularExpression::CaseInsensitiveOption);
    rule.format = typeFormat;
    HighlightingRules.append(rule);
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach(const HighlightingRule &rule, HighlightingRules)
    {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text); //matches every occurance.
        while(matchIterator.hasNext()){
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(),rule.format);
        }
    }
}
