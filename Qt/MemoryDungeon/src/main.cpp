#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setFixedSize(1180, 728);

    int width = w.frameGeometry().width();
    int height = w.frameGeometry().height();

    QScreen *screen = a.primaryScreen();

    int screenWidth = screen->geometry().width();
    int screenHeight = screen->geometry().height();

    w.setGeometry((screenWidth/2)-(width/2), (screenHeight/2)-(height/2), width, height);

    w.show();
    return a.exec();
}
