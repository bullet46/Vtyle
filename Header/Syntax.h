///:此类用于代码的高亮操作

#ifndef QSSEDITOR_SYNTAX_H
#define QSSEDITOR_SYNTAX_H
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>
#include <QTextDocument>
#include <QFile>

class Syntax:public QSyntaxHighlighter{
    Q_OBJECT
public:
    Syntax(QTextDocument* d);

protected:
    void highlightBlock(const QString &text) override;

};

#endif //QSSEDITOR_SYNTAX_H
