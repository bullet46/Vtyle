#include "../Header/Syntax.h"

Syntax::Syntax(QTextDocument *d): QSyntaxHighlighter(d) {

}

void Syntax::highlightBlock(const QString &text) {
    QFile propertyValLightFile("./Resource/syntax/propertyVal.txt");
    QString propertyValLight;
    if(propertyValLightFile.open(QIODevice::ReadOnly))
    {
        propertyValLight=propertyValLightFile.readAll();
    }
    //属性的值
    QFile propertyLightFile("./Resource/syntax/property.txt");
    QString propertyLight;
    if(propertyLightFile.open(QIODevice::ReadOnly))
    {
        propertyLight=propertyLightFile.readAll();
    }
    //属性
    QFile classNameLightFile("./Resource/syntax/className.txt");
    QString classNameLight;
    if(classNameLightFile.open(QIODevice::ReadOnly))
    {
        classNameLight=classNameLightFile.readAll();
    }
    //关键字之类的
    //一些配置的读取


    QTextCharFormat format;
    QRegularExpression reg;
    QRegularExpressionMatchIterator iter;
    //采用全局的正则和格式化  减少不必要的浪费

    //一些值的高亮  类似px啊 #000这些
    format.setForeground(QColor(0, 206, 209));
    format.setFontWeight(QFont::Bold);
    reg.setPattern(propertyValLight);
    iter=reg.globalMatch(text);
    while(iter.hasNext())
    {
        QRegularExpressionMatch match=iter.next();
        setFormat(match.capturedStart(),match.capturedLength(),
                  format);
    }
    //属性值

    format.setForeground(QColor(0, 207, 189));
    format.setFontWeight(QFont::Bold);
    reg.setPattern(classNameLight);
    iter=reg.globalMatch(text);
    while(iter.hasNext())
    {
        QRegularExpressionMatch match=iter.next();
        setFormat(match.capturedStart(),match.capturedLength(),
                  format);
    }
    //类名高亮

    format.setForeground(QColor(212, 156, 155));
    format.setFontWeight(QFont::Bold);
    reg.setPattern("{|}");
    iter=reg.globalMatch(text);
    while(iter.hasNext())
    {
        QRegularExpressionMatch match=iter.next();
        setFormat(match.capturedStart(),match.capturedLength(),
                  format);
    }
    //括号高亮

    format.setForeground(QColor(238,58,140));
    format.setFontWeight(QFont::Bold);
    reg.setPattern(propertyLight);
    iter=reg.globalMatch(text);
    while(iter.hasNext())
    {
        QRegularExpressionMatch match=iter.next();
        setFormat(match.capturedStart(),match.capturedLength(),
                  format);
    }
    //属性
}