#include "collectiondialog.h"
#include "ui_collectiondialog.h"

CollectionDialog::CollectionDialog(QWidget *parent, User* user, int maxK, int maxSp, int offset) :
    QDialog(parent),
    ui(new Ui::CollectionDialog)
{
    ui->setupUi(this);

    setWindowFlags( Qt::FramelessWindowHint | Qt::Dialog);

    this->user = user;
    this->maxK = maxK;
    this->maxSp = maxSp;
    this->offset = offset;

    this->curPos = 0;
    ui->leftBtn->setVisible(false); // cannot go left at the beginning

    ui->rateLbl->setText(QString::fromStdString(to_string(user->getCollectionRate()) + "%"));

    this->cardLblArr = new QLabel*[5];
    this->cardLblArr[0] = ui->cardLbl1;
    this->cardLblArr[1] = ui->cardLbl2;
    this->cardLblArr[2] = ui->cardLbl3;
    this->cardLblArr[3] = ui->cardLbl4;
    this->cardLblArr[4] = ui->cardLbl5;

    this->indexLblArr = new QLabel*[5];
    this->indexLblArr[0] = ui->indexLbl1;
    this->indexLblArr[1] = ui->indexLbl2;
    this->indexLblArr[2] = ui->indexLbl3;
    this->indexLblArr[3] = ui->indexLbl4;
    this->indexLblArr[4] = ui->indexLbl5;

    this->updateShowcase();

    connect(ui->rightBtn, &QPushButton::released, this, [=]() {
        (this->curPos)++;

        ui->leftBtn->setVisible(true);

        this->updateShowcase();

        if (this->curPos + 5 >= (this->maxK + this->maxSp)) {
            ui->rightBtn->setVisible(false);
        }
    });

    connect(ui->leftBtn, &QPushButton::released, this, [=]() {
        (this->curPos)--;

        ui->rightBtn->setVisible(true);

        this->updateShowcase();

        if (this->curPos <= 0) {
            ui->leftBtn->setVisible(false);
        }
    });
}

CollectionDialog::~CollectionDialog()
{
    delete [] this->cardLblArr;
    delete [] this->indexLblArr;

    delete ui;
}

void CollectionDialog::updateShowcase() {
    QMovie* movie;
    for (int p = 0; p < 5; p++)
    {
        if ((this->curPos + p) >= this->maxK)
        {
            // Special kind
            if (this->user->getOwnedSp()[this->curPos + p - this->maxK]) {
                movie = new QMovie(QString::fromStdString(":/images/cards/" + to_string(-(this->curPos + p - this->maxK) + this->offset) + ".gif"));

            }
            else {
                movie = new QMovie(":/images/cards/p.png");
            }

            this->indexLblArr[p]->setText(QString::fromStdString("Sp." + to_string(this->curPos + p - this->maxK + 1)));
        }
        else
        {
            // Normal kind
            if (this->user->getOwnedK()[this->curPos + p]) {
                movie = new QMovie(QString::fromStdString(":/images/cards/" + to_string(this->curPos + p + 1) + ".gif"));
            }
            else {
                movie = new QMovie(":/images/cards/p.png");
            }

            this->indexLblArr[p]->setText(QString::fromStdString("No." + to_string(this->curPos + p + 1)));
        }

        this->cardLblArr[p]->setMovie(movie);
        movie->start();
    }
}

void CollectionDialog::keyPressEvent(QKeyEvent *e)
{
    if (e -> key() == Qt::Key_Escape ||
        e ->key() == Qt::Key_Enter ||
        e->key() == Qt::Key_Return) {
        return;
    }

    QDialog::keyPressEvent(e);
}
