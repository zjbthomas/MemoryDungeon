#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QScreen>

#include <QTimer>
#include <QPushButton>

#include "qmovie.h"

#include "gamerules/gamerule.h"
#include "users/user.h"

#include "widgets/userlogindialog.h"
#include "widgets/messagedialog.h"
#include "widgets/shopdialog.h"
#include "widgets/jumpdialog.h"
#include "widgets/collectiondialog.h"
#include "widgets/herodialog.h"

#include "widgets/clickablelabel.h"
#include "widgets/clickableprogressbar.h"

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

    const static int ADDGOLD = 3;
    const static int JUMPCOST = 5;

    // methods
    ClickableLabel* searchByN(int);

    void initUI();
    void initWindow();
    void initCardGL();
    void initTexts();
    void initPBs();
    void initTimers();

    void makeConnections();

    void initGame();

    void updateAllCards();
    int updateOneCard(int n);

    void updateSidebar(bool);

    // for updating progress bars
    void updateItemPB();

    void updateLevelPB();
    void updateAmPB();
    void updateHpPB();

    void performClick(int);

    void start(bool);

    // UI related
    Ui::MainWindow *ui;

    ClickableProgressBar* itemPB;

    QTimer* amTimer;
    QTimer* settleTimer;
    QTimer* aiTimer;

    // Game system related
    GameRule* game;
    User* user;
    int floorType;
    bool foundTreasure;
    bool enabledHeroBtn;
};
#endif // MAINWINDOW_H
