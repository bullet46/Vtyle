#include <QApplication>
#include "../Header/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow mainWindow;
    mainWindow.resize(1200,800);
    mainWindow.setWindowTitle("Vtyle");
    mainWindow.setWindowIcon(QIcon("./Resource/QStyleIcon.ico"));
    mainWindow.showMaximized();

    return QApplication::exec();
}
