#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>

#include "users/user.h"

void setToScreenCenter(QWidget* widget, QScreen* screen) {
    int screenWidth = screen->geometry().width();
    int screenHeight = screen->geometry().height();

    int width = widget->frameGeometry().width();
    int height = widget->frameGeometry().height();
    widget->setGeometry((screenWidth/2)-(width/2), (screenHeight/2)-(height/2), width, height);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //a.setWindowIcon(QIcon(":/images/screens/app.ico"));

    const static int MAXK = 20;
    const static int MAXSP = 6;
    User* user = new User(MAXK, MAXSP);

    UserLoginDialog* userLoginDialog = new UserLoginDialog(nullptr, user);
    setToScreenCenter(userLoginDialog, a.primaryScreen());

    if (userLoginDialog->exec() == QDialog::Accepted) {
        w.initWithUser(user, MAXK, MAXSP);

        w.setFixedSize(1180, 728);

        setToScreenCenter(&w, a.primaryScreen());

        w.show();
    }

    delete userLoginDialog;

    return a.exec();
}
