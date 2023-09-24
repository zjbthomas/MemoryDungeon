#include "shopdialog.h"
#include "ui_shopdialog.h"

ShopDialog::ShopDialog(QWidget *parent, User* user) :
    QDialog(parent),
    ui(new Ui::ShopDialog)
{
    ui->setupUi(this);

    setWindowFlags( Qt::FramelessWindowHint | Qt::Dialog);

    this->user = user;

    ui->goldLbl->setText(QString::number(this->user->getGold()));

    this->timer = new QTimer(this);
    connect(this->timer, &QTimer::timeout, this, [=]() {
        this->repaintLbl();
    });

    for (int c = 0; c < 5; c++) {
        for (int r = 0; r < 2; r++) {
            int n = r * 5 + c;

            // create button
            ClickableLabel* cardLbl = new ClickableLabel(nullptr, n);
            cardLbl->setFixedSize(QSize(64, 64));
            cardLbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            // initial background
            QMovie* movie = new QMovie(":/images/cards/p.png");
            cardLbl->setMovie(movie);
            movie->start();

            // set size policy
            QSizePolicy policy = cardLbl->sizePolicy();
            policy.setRetainSizeWhenHidden(true);
            cardLbl->setSizePolicy(policy);

            // set connection
            connect(cardLbl, &ClickableLabel::released, this, [=]() {
                if ((!this->timer->isActive()) &&
                    (this->user->getGold() >= this->price))
                {
                    this->activeLbl = cardLbl;

                    cardLbl->setIsClickable(false);

                    this->x = 0;
                    this->cycle = 1;

                    int kind = this->price;

                    this->price--;
                    ui->priceLbl->setText(QString::fromStdString(to_string(this->price) + "C"));

                    // Dealing with purchase action.
                    this->isNewKind = this->user->gachaK(&kind);
                    this->gachaPath = ":/images/cards/" + to_string(kind) + ".gif";

                    if (this->isNewKind) {
                        ui->goldLbl->setText(QString::number(this->user->getGold()));
                    } else {
                        ui->goldLbl->setText(QString::number(this->user->getGold() - 1)); // TODO: why such logic?
                    }

                    ui->infoTB->setText("Finding...");

                    this->timer->start(10);
                }
                else if (this->user->getGold() < this->price)
                {
                    ui->infoTB->setText("Not enough credit.");
                }
            });

            ui->showcaseGL->addWidget(cardLbl, r, c);
        }
    }

    connect(ui->closeBtn, &QPushButton::released, this, [=]() {
        if ((!this->timer->isActive())) {
            if (this->hasGift) {
                string msg = string("Thanks for drawing 10 times!\n") + \
                            "You get a free gift!\n" + \
                            "Please receive it!";

                MessageDialog* messageDialog = new MessageDialog(this, msg, "Wow", true, this->user);
                messageDialog->setModal(true);
                messageDialog->exec();
                delete messageDialog;
            }

            this->close();
        }
    });
}

ShopDialog::~ShopDialog()
{
    delete this->timer;

    delete ui;
}

void ShopDialog::repaintLbl() {
    QPixmap pixmap = QPixmap(":/images/cards/p.png");

    int w = this->activeLbl->width();
    int h = this->activeLbl->height();

    if (!this->timer->isActive()) {
        this->activeLbl->setPixmap(pixmap.scaled(w - 2 * this->x, h));
        return;
    }

    if (this->x < w / 2) {
        this->activeLbl->setPixmap(pixmap.scaled(w - 2 * this->x, h));
        this->x += 16;
    } else if (this->x < w) {
        if (this->cycle == 5) {
            QPixmap tempPixmap = QPixmap(QString::fromStdString(gachaPath));
            this->activeLbl->setPixmap(tempPixmap.scaled(w - 2 * this->x, h).transformed(QTransform().scale(-1,1)));
            this->x += 16;
        } else {
            this->activeLbl->setPixmap(pixmap.scaled(w - 2 * this->x, h).transformed(QTransform().scale(-1,1)));
            this->x += 16;
        }
    } else {
        if (this->cycle == 5) {
            QMovie* movie = new QMovie(QString::fromStdString(gachaPath));
            this->activeLbl->setMovie(movie);
            movie->setScaledSize(QSize(w, h));
            movie->start();

            this->timer->stop();

            if (this->isNewKind) {
                ui->infoTB->setText("You find part of your memory!");
            } else {
                ui->infoTB->setText("Sorry, you are not lucky enough this time.");

                ui->goldLbl->setText(QString::number(this->user->getGold()));
            }

            if (this->price == 0) {
                this->hasGift = true;
            }
        } else {
            this->activeLbl->setPixmap(pixmap.scaled(w, h));

            this->cycle ++;
            this->x = 0;

            this->timer->setInterval(this->timer->interval() + 10);
        }
    }

}


void ShopDialog::showEvent(QShowEvent *e)
{
    QRect parentRect( parentWidget()->mapToGlobal( QPoint( 0, 0 ) ),
                     parentWidget()->size() );
    move( QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, size(),
                             parentRect ).topLeft() );
}

void ShopDialog::keyPressEvent(QKeyEvent *e)
{
    if (e -> key() == Qt::Key_Escape ||
        e ->key() == Qt::Key_Enter ||
        e->key() == Qt::Key_Return) {
        return;
    }

    QDialog::keyPressEvent(e);
}
