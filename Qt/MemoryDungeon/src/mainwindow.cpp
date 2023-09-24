#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete this->game;
    delete this->user;

    delete this->itemPB;

    delete this->amTimer;
    delete this->settleTimer;
    delete this->aiTimer;

    delete ui;
}

void MainWindow::initWithUser(User* user, int maxK, int maxSp) {
    this->user = user;

    this->maxK = maxK;
    this->maxSp = maxSp;

    this->game = new GameRule(this->MAXR, this->MAXC, maxK, maxSp, this->user->getOwnedK(), this->user->getOwnedSp());

    initUI();
    initGame();

    this->updateSidebar(false);
}

void MainWindow::initUI() {
    this->initWindow();
    this->initCardGL();
    this->initTexts();
    this->initPBs();
    this->initTimers();

    this->makeConnections();
}

void MainWindow::initWindow() {
    // Remove title bar
    // source: https://stackoverflow.com/questions/3948441/how-to-remove-the-window-border-containing-minimize-maximize-and-close-buttons
    setWindowFlags( Qt::FramelessWindowHint );

    // Fix window size
    //this->setFixedSize(1180, 728);
}


void MainWindow::initCardGL() {
    for (int c = 0; c < this->MAXC; c++) {
        for (int r = 0; r < this->MAXR; r++) {
            int n = r * this->MAXC + c;

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

            // set connection
            connect(cardLbl, &ClickableLabel::released, this, [=]() {
                this->performClick(cardLbl->getPos());
            });

            // defult invisible
            cardLbl->setVisible(false);

            ui->cardGL->addWidget(cardLbl, this->MAXR - (r + 1), c);
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

        ui->nextFloorBtn->setVisible(true);

        ui->levelLbl->setText(QString::number(this->user->getSavedLevel()));
    }

    ui->goldLbl->setText(QString::number(this->user->getGold()));

    ui->gainLbl->setVisible(false);
    ui->evilLbl->setVisible(false);

    ui->newGameBtn->setVisible(false);
    ui->pauseBtn->setVisible(false);
    ui->resumeBtn->setVisible(false);
}

void MainWindow::initPBs() {
    // set statusLbl to invisible as well
    ui->statusLbl->setVisible(false);

    QString pbStyle = "QProgressBar {border: 2px solid black; background:black; color: white} ";

    QString amPBStyle = "QProgressBar::chunk {background-color: blue;}";
    ui->amPB->setStyleSheet(pbStyle + amPBStyle);

    QString hpPBStyle = "QProgressBar::chunk {background-color: red;}";
    ui->hpPB->setStyleSheet(pbStyle + hpPBStyle);

    // dynamically create item progress bar
    this->itemPB = new ClickableProgressBar();
    this->itemPB->setGeometry(QRect(965, 142, 140, 20));

    // TODO: temporarily using amPB's settings
    this->itemPB->setFont(ui->amPB->font());
    this->itemPB->setAlignment(ui->amPB->alignment());

    this->layout()->addWidget(this->itemPB);

    QString itemPBStyle = "QProgressBar::chunk {background-color: green;}";
    this->itemPB->setStyleSheet(pbStyle + itemPBStyle);

    ui->levelPB->setVisible(false);
    ui->amPB->setVisible(false);
    ui->hpPB->setVisible(false);

    // update itemPB
    this->itemPB->setVisible(true);
    this->updateItemPB();
}

void MainWindow::initTimers() {
    this->amTimer = new QTimer(this);

    this->settleTimer = new QTimer(this);
    this->settleTimer->setSingleShot(true);

    this->aiTimer = new QTimer(this);
    this->aiTimer->setSingleShot(true);
}

void MainWindow::makeConnections() {
    // next level button
    connect(ui->nextFloorBtn, &QPushButton::released, this, [=]() {
        this->start(false);
    });

    // new game button
    connect(ui->newGameBtn, &QPushButton::released, this, [=]() {
        this->game->setLevel(this->user->getSavedLevel());

        this->start(false);
    });

    // pause button
    connect(ui->pauseBtn, &QPushButton::released, this, [=]() {
        if (!this->settleTimer->isActive()) {
            this->amTimer->stop();

            ui->newGameBtn->setVisible(true);
            ui->pauseBtn->setVisible(false);
            ui->resumeBtn->setVisible(true);

            ui->statusLbl->setVisible(false);
            ui->gainLbl->setVisible(false);

            this->updateSidebar(false);
        }
    });

    // resume button
    connect(ui->resumeBtn, &QPushButton::released, this, [=]() {
        ui->newGameBtn->setVisible(false);
        ui->pauseBtn->setVisible(true);
        ui->resumeBtn->setVisible(false);

        this->updateSidebar(true);

        this->amTimer->start(100);
    });

    // hero button
    connect(ui->heroBtn, &QPushButton::released, this, [=]() {
        if (this->enabledHeroBtn) {
            HeroDialog* heroDialog = new HeroDialog(this, this->user);
            heroDialog->setModal(true);
            heroDialog->exec();
            delete heroDialog;

            this->game->setHero(this->user->getHero());

            ui->heroBtn->setIcon(QIcon(QString::fromStdString(":images/heroes/" + to_string(this->game->getHero()) + ".png")));
        }
    });

    // collection progress bar
    connect(this->itemPB, &ClickableProgressBar::released, this, [=] (){
        CollectionDialog* collecitonDialog = new CollectionDialog(this, this->user, this->maxK, this->maxSp, this->OFFSET);
        collecitonDialog->setModal(true);
        collecitonDialog->exec();
        delete collecitonDialog;
    });

    // shop button
    connect(ui->shopBtn, &QPushButton::released, this, [=]() {
        ShopDialog* shopDialog = new ShopDialog(this, this->user);
        shopDialog->setModal(true);
        shopDialog->exec();
        delete shopDialog;

        this->updateSidebar(false);

        ui->goldLbl->setText(QString::number(this->user->getGold()));

        this->updateItemPB();
    });

    // jump button
    connect(ui->jumpBtn, &QPushButton::released, this, [=]() {
        // Minus credit, write to the user file and refresh to show.
        this->user->setGold(this->user->getGold() - this->JUMPCOST);
        this->user->writeFile();

        ui->goldLbl->setText(QString::number(this->user->getGold()));

        this->updateSidebar(false);

        // Show the message.
        string msg = string("You pay ") + to_string(this->JUMPCOST) + " credits to buy the items.\n" + \
                    "Ready to choose the next floor!";

        MessageDialog* messageDialog = new MessageDialog(this, msg, "Jumping", false, this->user);
        messageDialog->setModal(true);
        messageDialog->exec();
        delete messageDialog;

        // Show the set form.
        JumpDialog* jumpDialog = new JumpDialog(this, this->game, this->user);
        jumpDialog->setModal(true);
        jumpDialog->exec();
        delete jumpDialog;

        // Acts like a new game.
        this->start(true);
    });

    // home button
    connect(ui->homeBtn, &QPushButton::released, this, [=]() {
        int gainGold = this->game->getLevel() / 3; // TODO: magic number
        this->user->setGold(this->user->getGold() + gainGold);

        this->game->setLevel(0);
        this->user->setSavedLevel(0);

        this->user->writeFile();

        ui->goldLbl->setText(QString::number(this->user->getGold()));

        ui->levelLbl->setText("0");
        ui->savedLbl->setText("0");

        // Acts like Game over.
        // Stop timing.
        this->amTimer->stop();

        // Clear the condition.
        ui->statusLbl->setVisible(false);
        ui->gainLbl->setVisible(false);

        this->updateSidebar(false);

        // Set the buttons.
        ui->newGameBtn->setVisible(true);
        ui->pauseBtn->setVisible(false);
        ui->resumeBtn->setVisible(false);

        ui->nextFloorBtn->setVisible(false);

        this->enabledHeroBtn = true;

        // Show message.
        string msg = string("Welcome back to your hometown!\n") + \
                     "Your conquests give you "+ to_string(gainGold) + " golds.\n" + \
                     "Ready to fight again!";

        MessageDialog* messageDialog = new MessageDialog(this, msg, "Welcome home!", false, this->user);
        messageDialog->setModal(true);
        messageDialog->exec();
        delete messageDialog;

    });

    // AI button
    connect(ui->aiBtn, &QPushButton::released, this, [=]() {
        // Set the level the saved one and open a new level.
        this->game->newAILevel(100 - this->user->getAIForgetRate());

        ui->levelLbl->setText("U");
        ui->levelLbl->setVisible(true);

        // Reset the score and time and reprint all.
        ui->levelPB->setVisible(true);
        this->updateLevelPB();

        ui->amPB->setVisible(false);
        ui->hpPB->setVisible(false);

        this->updateSidebar(false);

        this->updateAllCards();

        // Set the buttons.
        ui->newGameBtn->setVisible(true);
        ui->pauseBtn->setVisible(false);
        ui->resumeBtn->setVisible(false);

        ui->nextFloorBtn->setVisible(false);

        this->enabledHeroBtn = true;

        // Show message.
        string msg = string("Ready to fight your master!\n") + \
                     "The forget percentage of your master is "+ to_string(100 - this->user->getAIForgetRate())+ "%!";

        MessageDialog* messageDialog = new MessageDialog(this, msg, "Get set!", false, this->user);
        messageDialog->setModal(true);
        messageDialog->exec();
        delete messageDialog;
    });

    // am timer
    connect(this->amTimer, &QTimer::timeout, this, [=]() {
        if (this->game->getTimeRemain() > 0) {
            this->game->setTimeRemain(this->game->getTimeRemain() - 1);
            this->updateAmPB();
        } else {
            // when helmet break
            if (!this->settleTimer->isActive()) {
                // pop new line
                bool survive = this->game->popRow(this->game->getPopN());
                if (survive) {
                    this->updateLevelPB();
                    this->updateHpPB();

                    this->updateAllCards();

                    ui->statusLbl->setVisible(false);
                    ui->gainLbl->setVisible(false);

                    this->updateAmPB(); // TODO: does the order matter here?
                } else {
                    // gameover
                    // stop timing
                    this->amTimer->stop();
                    this->settleTimer->stop();

                    // reset everything
                    ui->levelLbl->setText("0");

                    ui->levelPB->setVisible(false);
                    ui->amPB->setVisible(false);
                    ui->hpPB->setVisible(false);

                    ui->statusLbl->setVisible(false);
                    ui->gainLbl->setVisible(false);

                    this->updateSidebar(false);

                    this->updateAllCards();

                    ui->newGameBtn->setVisible(true);
                    ui->pauseBtn->setVisible(false);
                    ui->resumeBtn->setVisible(false);

                    this->enabledHeroBtn = true;

                    // gameover message
                    MessageDialog* messageDialog = new MessageDialog(this, "Time's Up!\nGameover.", "Gameover", false, this->user);
                    messageDialog->setModal(true);
                    messageDialog->exec();
                    delete messageDialog;
                }
            }
        }
    });

    // settle timer
    connect(this->settleTimer, &QTimer::timeout, this, [=]() {
        // get score, and re-print all.
        bool winGame;
        int status;
        this->game->settle(&winGame, &status);

        this->updateHpPB();

        // update status
        switch (status)
        {
        case GameRule::SCORE:
            ui->statusLbl->setPixmap(QPixmap(":images/screens/score.png"));
            ui->statusLbl->setVisible(true);

            break;
        case GameRule::BONUS:
            ui->statusLbl->setPixmap(QPixmap(":images/screens/bonus.png"));
            ui->statusLbl->setVisible(true);

            break;
        case GameRule::CREDIT:
            ui->statusLbl->setPixmap(QPixmap(":images/screens/bonus.png"));
            ui->statusLbl->setVisible(true);

            ui->gainLbl->setVisible(true);

            break;
        case GameRule::COMBO:
            ui->statusLbl->setPixmap(QPixmap(":images/screens/combo.png"));
            ui->statusLbl->setVisible(true);

            break;
        case GameRule::BREAK:
            ui->statusLbl->setPixmap(QPixmap(":images/screens/break.png"));
            ui->statusLbl->setVisible(true);

            break;
        case GameRule::CRITICAL:
            ui->statusLbl->setPixmap(QPixmap(":images/screens/critical.png"));
            ui->statusLbl->setVisible(true);

            break;
        }

        this->updateLevelPB();

        this->updateAllCards();

        string msg = "";
        if (winGame) // If go to the next level.
        {
            this->amTimer->stop();

            // Rewards to the game.
            if (foundTreasure)
            {
                msg="You find a gift in this floor!\nPlease receive it!";

                MessageDialog* messageDialog = new MessageDialog(this, msg, "Wow!", true, this->user);
                messageDialog->setModal(true);
                messageDialog->exec();
                delete messageDialog;

            }

            switch (this->floorType)
            {
            case GameRule::NORMAL:
                this->user->setGold(this->user->getGold() + 1);

                break;
            case GameRule::CLOWN:
                this->user->setGold(this->user->getGold() + 3);

                break;
            case GameRule::EVIL:
                this->user->setGold(this->user->getGold() + 5);

                msg="You get the chest from beating EVIL!\nLet's open it!";

                MessageDialog* messageDialog = new MessageDialog(this, msg, "Wow!", true, this->user);
                messageDialog->setModal(true);
                messageDialog->exec();
                delete messageDialog;

                break;
            }

            // update user file as credit changed
            this->user->writeFile();

            ui->goldLbl->setText(QString::number(this->user->getGold()));

            this->updateItemPB();

            // hide progress bars
            ui->levelPB->setVisible(false);

            ui->amPB->setVisible(false);
            ui->hpPB->setVisible(false);

            this->updateSidebar(false);

            // hide status
            ui->statusLbl->setVisible(false);
            ui->goldLbl->setVisible(false);

            this->updateAllCards();

            // Set the buttons.
            ui->pauseBtn->setVisible(false);
            ui->resumeBtn->setVisible(false);

            this->enabledHeroBtn = true;

            // update saved level and write to user file
            this->user->setSavedLevel(this->game->getLevel());

            ui->savedLbl->setText(QString::number(this->game->getLevel()));

            if (this->game->getLevel() > this->user->getBestLevel()) {
                this->user->setBsetLevel(this->game->getLevel());

                ui->bestLbl->setText(QString::number(this->game->getLevel()));
            }

            this->user->writeFile();

            // Show the button to the next floor.
            ui->infoTB->setText(QString::fromStdString("Well done!\nLet's go to the next floor!"));

            ui->nextFloorBtn->setVisible(true);
        }
    });

    // AI settle timer
    connect(this->aiTimer, &QTimer::timeout, this, [=]() {
        bool winGame = false;
        int status;
        if (!this->game->getIsAITurn())
        {
            this->game->settleAI(&winGame, &status); // this will update AI's status

            if (status == GameRule::SCORE) {
                this->updateLevelPB();

                ui->statusLbl->setPixmap(QPixmap(":images/screens/score.png"));
                ui->statusLbl->setVisible(true);
            }

            this->updateAllCards();

            // change to AI's turn
            if (this->game->getIsAITurn()) {
                ui->levelLbl->setText(QString::fromStdString("M"));

                ui->newGameBtn->setVisible(false);

                this->updateSidebar(true);

                this->aiTimer->start(1000);
            }
        }
        else
        {
            switch (this->game->aiAction())
            {
            case 1:
                this->game->settleAI(&winGame, &status); // this will update AI's status

                if (status == GameRule::AISCORE)
                {
                    this->updateLevelPB();

                    ui->statusLbl->setPixmap(QPixmap(":images/screens/break.png"));
                    ui->statusLbl->setVisible(true);
                }

                // Change to player's turn.
                if (!this->game->getIsAITurn())
                {

                    ui->levelLbl->setText(QString::fromStdString("U"));

                    ui->newGameBtn->setVisible(true);

                    this->updateSidebar(true);
                }
                break;
            case 2:
                this->aiTimer->start(1000);
                break;
            case 3:
                this->aiTimer->start(1000);
                break;
            }

            this->updateAllCards();

            if (this->game->getIsAITurn())
            {
                // Maintain in AI's turn.
                this->aiTimer->start(1000);
            }
        }
        if (winGame)
        {
            string msg = "";
            if (this->game->getScore() == this->game->getAIScore())
            {
                msg = "You get the same score as your master.\nPlease start another training!";

                ui->infoTB->setText(QString::fromStdString(msg));

                MessageDialog* messageDialog = new MessageDialog(this, msg, "Draw", true, this->user);
                messageDialog->setModal(true);
                messageDialog->exec();
                delete messageDialog;
            }

            if (this->game->getScore() > this->game->getAIScore())
            {
                // First give player extra credits.
                int gainGold = (this->game->getScore() - this->game->getAIScore()) / 4 + 1;
                this->user->setGold(this->user->getGold() + gainGold);

                // Adjust the AI remember percentage.
                int adjustment = this->game->getScore() - this->game->getAIScore(); // A positive number.
                if (this->user->getAIForgetRate() + adjustment <= 100) {
                    this->user->setAIForgetRate(this->user->getAIForgetRate() + adjustment);
                }
                else {
                    this->user->setAIForgetRate(100);
                }

                this->user->writeFile();

                ui->goldLbl->setText(QString::number(this->user->getGold()));

                msg = string("Congratulations! You win your master!\n") + \
                      "You have earn "+ to_string(gainGold) + " credits!\n" + \
                      "Please start a new training to win more!";

                MessageDialog* messageDialog = new MessageDialog(this, msg, "Win", false, this->user);
                messageDialog->setModal(true);
                messageDialog->exec();
                delete messageDialog;
            }

            if (this->game->getScore() < this->game->getAIScore())
            {
                // Adjust the AI remember percentage.
                int adjustment = this->game->getScore() - this->game->getAIScore(); // A negative number.
                if (this->user->getAIForgetRate() + adjustment >= 0) {
                    this->user->setAIForgetRate(this->user->getAIForgetRate() + adjustment);
                }
                else {
                    this->user->setAIForgetRate(0);
                }

                this->user->writeFile();

                msg = string("Sorry you lose this time!\n") + \
                      "Please start a new training and try again!";

                MessageDialog* messageDialog = new MessageDialog(this, msg, "Lose", false, this->user);
                messageDialog->setModal(true);
                messageDialog->exec();
                delete messageDialog;

            }

            // Set score and time to zero, re-print all.
            this->updateLevelPB();

            // Clear the condition.
            ui->statusLbl->setVisible(false);
            ui->gainLbl->setVisible(false);

            this->updateSidebar(false);

            this->updateAllCards();

            // Set the buttons.
            ui->newGameBtn->setVisible(true);
            this->enabledHeroBtn = true;
        }
    });
}

void MainWindow::initGame() {
    this->game->setLevel(this->user->getSavedLevel());

    this->user->writeFile();

    this->game->setHero(this->user->getHero());

    ui->heroBtn->setIcon(QIcon(QString::fromStdString(":images/heroes/" + to_string(this->game->getHero()) + ".png")));
    this->enabledHeroBtn = true;
}

void MainWindow::updateAllCards() {
    for (int n = 0; n < this->MAXC * this->MAXR; n++) {
        this->updateOneCard(n);
    }
}

void MainWindow::updateSidebar(bool isRunning) {
    ui->shopBtn->setVisible(!isRunning);
    ui->jumpBtn->setVisible(!isRunning && this->user->getGold() >= 5); // TODO: magic number here
    ui->homeBtn->setVisible(!isRunning);
    ui->aiBtn->setVisible(!isRunning);
}

void MainWindow::updateItemPB() {
    this->itemPB->setMinimum(0);
    this->itemPB->setMaximum(100);
    this->itemPB->setValue(this->user->getCollectionRate());
}

void MainWindow::updateLevelPB() {
    // TODO: check if everything is correct here
    if (this->game->getIsAIMode() == false) {
        if (this->floorType == GameRule::NORMAL) {
            QString pbStyle = "QProgressBar {border: 2px solid black; background:black;} ";
            QString levelPBStyle = "QProgressBar::chunk {background-color: yellow;}";
            ui->levelPB->setStyleSheet(pbStyle + levelPBStyle);

            ui->levelPB->setMinimum(0);
            ui->levelPB->setMaximum(this->game->getObjective());
            ui->levelPB->setValue(this->game->getScore());
        } else {
            QString pbStyle = "QProgressBar {border: 2px solid black; background:black;} ";
            QString levelPBStyle = "QProgressBar::chunk {background-color: red;}";
            ui->levelPB->setStyleSheet(pbStyle + levelPBStyle);

            ui->levelPB->setMinimum(0);
            ui->levelPB->setMaximum(this->game->getObjective());
            ui->levelPB->setValue(this->game->getObjective() - this->game->getScore()); // value reserse
        }
    } else {
        QString pbStyle = "QProgressBar {border: 0px; background:red;} ";
        QString levelPBStyle = "QProgressBar::chunk {background-color: blue;}";
        ui->levelPB->setStyleSheet(pbStyle + levelPBStyle);

        ui->levelPB->setMinimum(0);
        if (this->game->getScore() + this->game->getAIScore() == 0) {
            ui->levelPB->setMaximum(2);
            ui->levelPB->setValue(1);
        } else {
            ui->levelPB->setMaximum(this->game->getScore() + this->game->getAIScore());
            ui->levelPB->setValue(this->game->getScore());
        }
    }
}

void MainWindow::updateAmPB() {
    ui->amPB->setMinimum(0);
    ui->amPB->setMaximum(this->game->getBaseTime() / 10);
    ui->amPB->setValue(this->game->getTimeRemain() / 10);
}

void MainWindow::updateHpPB() {
    if (this->game->updateCurrentR() + this->game->getPopN() > this->MAXR) {
        ui->heroBtn->setIcon(QIcon(QString::fromStdString(":images/heroes/" + to_string(this->game->getHero()) + "_d.png")));
    } else {
        ui->hpPB->setMinimum(0);
        ui->hpPB->setMaximum(this->MAXR);
        ui->hpPB->setValue(this->game->updateCurrentR() - 1);

        ui->heroBtn->setIcon(QIcon(QString::fromStdString(":images/heroes/" + to_string(this->game->getHero()) + ".png")));
    }
}
ClickableLabel* MainWindow::searchByN(int n) {
    int r = n / this->MAXC;
    int c = n % this->MAXC;

    QWidget* widget = ui->cardGL->itemAtPosition(this->MAXR - (r + 1), c)->widget();
    return dynamic_cast<ClickableLabel*>(widget);
}

void MainWindow::performClick(int n) {
    if (this->game->getIsAIMode() == false) {

        if (this->amTimer->isActive() &&
            !this->settleTimer->isActive() &&
            this->game->isCardClickable(n)) {
            // game is running and not in settle phase
            // hide status
            ui->statusLbl->setVisible(false);

            ui->gainLbl->setVisible(false);

            switch (this->game->performClick(n)) {
            case 0:
                this->updateOneCard(n);
                break;
            case 1:
                this->settleTimer->start(300);

                this->updateOneCard(n);
                break;
            case Row::REINFORCE:
                // for HUNTER, decrease credit
                if ((this->game->getHero() == GameRule::HUNTER) &&
                    (this->user->getGold() >= 1)) {
                    this->user->setGold(this->user->getGold() - 1);
                    this->user->writeFile(); // TODO: the location of this line is moved; also, is this called too frequent?

                    ui->goldLbl->setText(QString::number(this->user->getGold()));

                    // update item bar, as credit changed
                    this->updateSidebar(true);
                }

                this->settleTimer->start(800);

                // update all cards as REINFORCE shows all cards
                this->updateAllCards();
                break;
            case Row::CHAOS:
                // for HUNTER, decrease credit
                if ((this->game->getHero() == GameRule::HUNTER) &&
                    (this->user->getGold() >= 1)) {
                    this->user->setGold(this->user->getGold() - 1);
                    this->user->writeFile(); // TODO: the location of this line is moved; also, is this called too frequent?

                    ui->goldLbl->setText(QString::number(this->user->getGold()));

                    // update item bar, as credit changed
                    this->updateSidebar(true);
                }

                this->settleTimer->start(1200);

                // update all cards as CHAOS shows all cards
                this->updateAllCards();
                break;
            case Row::GOLD:
                this->user->setGold(this->user->getGold() + this->ADDGOLD);

                // for HUNTER, add more credits
                if ((this->game->getHero() == GameRule::HUNTER)) {
                    this->user->setGold(this->user->getGold() + this->ADDGOLD);
                }

                this->user->writeFile();

                ui->goldLbl->setText(QString::number(this->user->getGold()));

                // update item bar, as credit changed
                this->updateSidebar(true);

                this->settleTimer->start(400);

                this->updateOneCard(n);
                break;
            case Row::MAP:
                this->settleTimer->start(500);

                this->updateAllCards();

                break;
            case Row::HEAL:
                this->updateAmPB();

                // TODO: why different times?
                if (this->game->getHero() != GameRule::MASTER) {
                    this->settleTimer->start(400);
                } else {
                    this->settleTimer->start(10);
                }

                this->updateOneCard(n);

                break;
            case Row::TREASURE:
                // for HUNTER, add credit
                if ((this->game->getHero() == GameRule::HUNTER)) {
                    this->user->setGold(this->user->getGold() + 1); // TODO: magic number

                    this->user->writeFile(); // TODO: the location of this line is moved; also, is this called too frequent?

                    ui->goldLbl->setText(QString::number(this->user->getGold()));

                    // update item bar, as credit changed
                    this->updateSidebar(true);
                }

                this->foundTreasure = true;

                this->settleTimer->start(400);

                this->updateOneCard(n);

                break;
            }
        }
    } else {
        // AI mode
        if (!this->aiTimer->isActive() &&
            (this->updateOneCard(n) == Row::COVER)) {
            // hide status
            ui->statusLbl->setVisible(false);

            ui->gainLbl->setVisible(false);

            switch (this->game->performClick(n)) {
            case 0:
                this->updateOneCard(n);
                break;
            case 1:
                this->aiTimer->start(300);

                this->updateOneCard(n);

                break;
            }
        }
    }
}

int MainWindow::updateOneCard(int n) {
    int d = this->game->getCardDisplay(n);

    string image = ":/images/cards/0.gif";
    bool isVisible = true;

    switch (d) {
    case Row::NE:
        isVisible = false;
        break;
    default:
        image = ":/images/cards/" + to_string(d) + ".gif";
        break;
    }

    // reveal HEAL for hero MASTER
    if ((this->game->getHero() == GameRule::MASTER) && (d == Row::HEAL)){
        image = ":/images/heroes/t.png";
    }

    ClickableLabel* cardLbl = this->searchByN(n);

    cardLbl->setVisible(isVisible);

    QMovie* movie = new QMovie(QString::fromStdString(image));
    cardLbl->setMovie(movie);
    movie->start();

    return d;
}

void MainWindow::start(bool isByConfig) {
    // reset variables
    this->floorType = GameRule::NORMAL;
    if (!isByConfig) {
        this->floorType = this->game->newLevel(); // start a new level
    }
    this->foundTreasure = false;

    // enable progress bars
    this->updateLevelPB();
    ui->levelPB->setVisible(true);
    this->updateAmPB();
    ui->amPB->setVisible(true);
    this->updateHpPB();
    ui->hpPB->setVisible(true);

    // set item bar
    this->updateSidebar(true);

    // hide status
    ui->statusLbl->setVisible(false);

    ui->gainLbl->setVisible(false);

    // update cards
    this->updateAllCards();

    // set buttons
    ui->newGameBtn->setVisible(false);
    ui->pauseBtn->setVisible(true);
    ui->resumeBtn->setVisible(false);

    ui->nextFloorBtn->setVisible(false);

    this->enabledHeroBtn = false;

    // setup the next level, MUST DONE AT THE END
    ui->levelLbl->setVisible(true);

    string msg = "";
    string title = "";

    switch (this->floorType) {
    case GameRule::NORMAL:
        ui->levelLbl->setText(QString::number(this->game->getLevel()));

        msg = to_string(this->game->getOwnedKN()) + " kinds of attacks, " + to_string(this->game->getEraseN()) + " identical attacks to hit.\n" + \
                     "Start with " + to_string(this->game->updateCurrentR()) + " rows, " + to_string(this->game->getPopN()) + " rows of reinforcement.\n" + \
                     "Your helmet will break every " + to_string(this->game->getTimeRemain() / 10) + " seconds.\n" + \
                     "You need to hit " + to_string(this->game->getObjective()) + " times. Good luck!";

        title = "Floor " + to_string(this->game->getLevel());

        ui->infoTB->setVisible(true);
        ui->infoTB->setText(QString::fromStdString(msg));

        ui->evilLbl->setVisible(false);

        break;
    case GameRule::CLOWN:
        ui->levelLbl->setText("C");

        msg = "A CLOWN FLOOR, try to survive!";

        title = "CLOWN FLOOR";

        ui->infoTB->setVisible(false);

        ui->evilLbl->setVisible(true);

        break;
    case GameRule::EVIL:
        ui->levelLbl->setText("E");

        msg = "An EVIL FLOOR, ready to suffer...";

        title = "EVIL FLOOR";

        ui->infoTB->setVisible(false);

        ui->evilLbl->setVisible(true);

        break;
    }

    MessageDialog* messageDialog = new MessageDialog(this, msg, title, false, this->user);
    messageDialog->setModal(true);
    messageDialog->exec();
    delete messageDialog;

    this->amTimer->start(100);
}
