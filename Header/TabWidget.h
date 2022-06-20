///:分页窗口类
#ifndef QSSEDITOR_TABWIDGET_H
#define QSSEDITOR_TABWIDGET_H
#include <QTabWidget>
#include <QFile>

class MainWindow;
class EditWidget;

class TabWidget:public QTabWidget {
Q_OBJECT
public:
    TabWidget(MainWindow* p=nullptr);
    void newEditWidget(const QString& title="*");
    //新建 title参数自己体会
    void addEditWidget(EditWidget* widget,const QString& title="*");
    //添加现有的窗口
private:
    MainWindow* win;
    //父窗口
};


#endif //QSSEDITOR_TABWIDGET_H
