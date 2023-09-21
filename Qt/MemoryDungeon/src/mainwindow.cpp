#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Game system related
    this->user = new User(this->MAXK, this->MAXSP);
    this->game = new GameRule(this->MAXR, this->MAXC, this->MAXK, this->MAXSP, this->user->getOwnedK(), this->user->getOwnedSp());

    // show login dialog first
    UserLoginDialog* userLoginDialog = new UserLoginDialog(this, this->user);
    userLoginDialog->setModal(true);
    userLoginDialog->exec();
    delete userLoginDialog;

    // UI related
    ui->setupUi(this);

    initUI();
    initGame();

    this->updateItemBar(false);
}

MainWindow::~MainWindow()
{
    delete this->game;
    delete this->user;

    delete ui;
}

void MainWindow::initUI() {
    initWindow();
    initCardGL();
    initTexts();
    initPBs();
}

void MainWindow::initWindow() {
    // Remove title bar
    // source: https://stackoverflow.com/questions/3948441/how-to-remove-the-window-border-containing-minimize-maximize-and-close-buttons
    setWindowFlags( Qt::CustomizeWindowHint );

    // Fix window size
    this->setFixedSize(1180, 728);
}


void MainWindow::initCardGL() {
    for (int c = 0; c < this->MAXC; c++) {
        for (int r = 0; r < this->MAXR; r++) {
            int n = r * this->MAXR + c;

            // create button
            ClickableLabel* cardLbl = new ClickableLabel(nullptr, n);
            cardLbl->setFixedSize(QSize(64, 64));

            // initial background
            QMovie* movie = new QMovie(":/images/cards/0.gif");
            cardLbl->setMovie(movie);
            movie->start();

            // set size policy
            QSizePolicy policy = cardLbl->sizePolicy();
            policy.setRetainSizeWhenHidden(true);
            cardLbl->setSizePolicy(policy);

            // movie is scaled
            cardLbl->setScaledContents(true);

            ui->cardGL->addWidget(cardLbl, r, c);
        }
    }
}

void MainWindow::initTexts() {
    ui->infoTB->setText("Come on to a new floor!");

    ui->userLbl->setText(QString::fromStdString(this->user->getUsername()));
    ui->bestLbl->setText(QString::number(this->user->getBestLevel()));
    ui->savedLbl->setText(QString::number(this->user->getSavedLevel()));

    if (this->user->getSavedLevel() != 0) {
        ui->newGameBtn->setVisible(false);

        this->nextLevelFlag = true;
        this->updateCardGL();

        ui->levelLbl->setText(QString::number(this->user->getSavedLevel()));
    }

    ui->goldLbl->setText(QString::number(this->user->getGold()));
}

void MainWindow::initPBs() {
    // set statusLbl to invisible as well
    ui->statusLbl->setVisible(false);

    QString pbStyle = "QProgressBar {border: 2px solid black; background:black;} ";

    QString levelPBStyle = "QProgressBar::chunk {background-color: yellow;}";
    ui->levelPB->setStyleSheet(pbStyle + levelPBStyle);

    QString amPBStyle = "QProgressBar::chunk {background-color: blue;}";
    ui->amPB->setStyleSheet(pbStyle + amPBStyle);

    QString hpPBStyle = "QProgressBar::chunk {background-color: red;}";
    ui->hpPB->setStyleSheet(pbStyle + hpPBStyle);

    QString itemPBStyle = "QProgressBar::chunk {background-color: green;}";
    ui->itemPB->setStyleSheet(pbStyle + itemPBStyle);

    ui->levelPB->setVisible(false);
    ui->amPB->setVisible(false);
    ui->hpPB->setVisible(false);

    // update itemPB
    ui->itemPB->setVisible(true);
    this->updateItemPB();
}

void MainWindow::initGame() {
    this->game->setLevel(this->user->getSavedLevel());

    this->user->writeFile();

    this->game->setHero(this->user->getHero());

    ui->heroBtn->setIcon(QIcon(QString::fromStdString(":images/heroes/" + to_string(this->game->getHero()) + ".png")));
    ui->heroBtn->setEnabled(true);
}

void MainWindow::updateCardGL() {
    if (nextLevelFlag) {
        // hide all cards
        for (int c = 0; c < this->MAXC; c++) {
            for (int r = 0; r < this->MAXR; r++) {

                ui->cardGL->itemAtPosition(r, c)->widget()->setVisible(false);
            }
        }

        // set next level label
        QWidget* widget = ui->cardGL->itemAtPosition(2, 3)->widget();
        ClickableLabel* cardLbl = dynamic_cast<ClickableLabel*>(widget);

        QMovie* movie = new QMovie(":/images/screens/button_next.png");
        cardLbl->setMovie(movie);
        movie->start();

        // show only the next level label
        cardLbl->setVisible(true);
    } else {
        // TODO
    }

}

void MainWindow::updateItemBar(bool isRunning) {
    ui->shopBtn->setVisible(!isRunning);
    ui->jumpBtn->setVisible(!isRunning && this->user->getGold() >= 5); // TODO: magic number here
    ui->homeBtn->setVisible(!isRunning);
    ui->aiBtn->setVisible(!isRunning);
}

void MainWindow::updateItemPB() {
    ui->itemPB->setMinimum(0);
    ui->itemPB->setMaximum(100);
    ui->itemPB->setValue(this->user->getCollectionRate());
}
