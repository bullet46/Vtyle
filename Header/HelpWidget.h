//:该类用于创建一个提供帮助的窗口
//这些帮助类似于选色器
#ifndef QSSEDITOR_HELPWIDGET_H
#define QSSEDITOR_HELPWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QLabel>
#include <QPainter>
#include "qdebug.h"
#include <Windows.h>
#include <QBitmap>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QScreen>
#include <QGuiApplication>
#include "math.h"

class SVWheel;
class ColorPicker;

class HWheel:public QWidget
{
Q_OBJECT
    //明度色轮（H）

public:
    HWheel();
    SVWheel* svWheel;
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event)override;
    void resizeEvent(QResizeEvent *event) override;
private:
    QPushButton* fullScreenColorPickButton;
    ColorPicker* picker;
};


class ColorPicker:public QWidget {
    Q_OBJECT
public:
    ColorPicker(QWidget* p);
    void pick();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    QWidget* wid;
    QPixmap photo;
};


class SVWheel:public QWidget{
    //S和V数值的调节
    Q_OBJECT
public:
    SVWheel();
    void svShow(QPoint pos,QColor color);

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QVBoxLayout* vLayout;
    QLabel* colorShow;
    QHBoxLayout* sValLayout;
        QLabel* sValText;
        QSpinBox* sSpinBox;
    QHBoxLayout* vValLayout;
        QLabel* vValText;
        QSpinBox* vSpinBox;
    QHBoxLayout* rgbLayout;
        QLabel* rgbText;
        QLineEdit* rgbVal;
    QHBoxLayout* htmlLayout;
        QLabel* htmlText;
        QLineEdit* htmlVal;

    QColor selfColor;
    void setS(int val)
    {
        int h=selfColor.hue(),v=selfColor.value();
        selfColor.setHsv(h,val,v);
        qDebug()<<selfColor.name();
        colorShow->setStyleSheet
        ("QLabel{background-color:"+selfColor.name()+";}");
        colorShow->update();
        rgbVal->setText(QString::number(selfColor.red())+","+
                        QString::number(selfColor.green())+","+
                        QString::number(selfColor.blue()));
        htmlVal->setText(selfColor.name());
    }
    void setV(int val)
    {
        qDebug()<<selfColor.name();
        int h=selfColor.hsvHue(),s=selfColor.hsvSaturation();
        selfColor.setHsv(h,s,val);

        colorShow->setStyleSheet
                ("QLabel{background-color:"+selfColor.name()+";}");
        colorShow->update();
        rgbVal->setText(QString::number(selfColor.red())+","+
                        QString::number(selfColor.green())+","+
                        QString::number(selfColor.blue()));
        htmlVal->setText(selfColor.name());
    }

};

#endif //QSSEDITOR_HELPWIDGET_H
