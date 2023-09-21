#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qmovie.h"

#include "gamerules/gamerule.h"
#include "users/user.h"

#include "widgets/userlogindialog.h"
#include "widgets/clickablelabel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // constants
    const static int MAXR = 6;
    const static int MAXC = 7;
    const static int MAXK = 20;
    const static int MAXSP = 6;
    const static int OFFSET = -2;

    // methods
    void initUI();
    void initWindow();
    void initCardGL();
    void initTexts();
    void initPBs();

    void initGame();

    void updateCardGL();

    void updateItemBar(bool);

    void updateItemPB();

    // UI related
    Ui::MainWindow *ui;

    // Game system related
    GameRule* game;
    User* user;
    int floorType;
    bool foundTreasure;

    bool nextLevelFlag = false;

};
#endif // MAINWINDOW_H
