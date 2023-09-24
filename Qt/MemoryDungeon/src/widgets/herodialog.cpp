#include "herodialog.h"
#include "ui_herodialog.h"

HeroDialog::HeroDialog(QWidget *parent, User* user) :
    QDialog(parent),
    ui(new Ui::HeroDialog)
{
    ui->setupUi(this);

    setWindowFlags( Qt::FramelessWindowHint | Qt::Dialog);

    for (int b = 0; b < 4; b++) {
        HoverPushButton* heroBtn = new HoverPushButton(this);

        heroBtn->setFixedHeight(728);
        heroBtn->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

        connect(heroBtn, &QPushButton::released, this, [=]() {
            user->setHero(b);
            user->writeFile();
            this->close();
        });

        connect(heroBtn, &HoverPushButton::enter, this, [=]() {
            ui->backgroundLbl->setPixmap(QPixmap(QString::fromStdString(":/images/heroes/bg" + to_string(b) + ".jpg")));
        });

        connect(heroBtn, &HoverPushButton::leave, this, [=]() {
            ui->backgroundLbl->setPixmap(QPixmap(QString::fromStdString(":/images/heroes/bg.jpg")));
        });

        ui->heroHL->addWidget(heroBtn);
    }

}

HeroDialog::~HeroDialog()
{
    delete ui;
}

void HeroDialog::showEvent(QShowEvent *e)
{
    QRect parentRect( parentWidget()->mapToGlobal( QPoint( 0, 0 ) ),
                     parentWidget()->size() );
    move( QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, size(),
                             parentRect ).topLeft() );
}


void HeroDialog::keyPressEvent(QKeyEvent *e)
{
    if (e -> key() == Qt::Key_Escape ||
        e ->key() == Qt::Key_Enter ||
        e->key() == Qt::Key_Return) {
        return;
    }

    QDialog::keyPressEvent(e);
}
