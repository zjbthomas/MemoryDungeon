#include "jumpdialog.h"
#include "ui_jumpdialog.h"

JumpDialog::JumpDialog(QWidget *parent, GameRule* game, User* user) :
    QDialog(parent),
    ui(new Ui::JumpDialog)
{
    ui->setupUi(this);

    setWindowFlags( Qt::FramelessWindowHint | Qt::Dialog);

    this->game = game;
    this->user = user;

    ui->kindSB->setMaximum(this->game->getOwnedKN());

    connect(ui->goBtn, &QPushButton::released, this, [=]() {
        int ruleN = ui->atkSB->value();
        int kind = ui->kindSB->value();
        int startR = ui->rowSB->value();
        int popN = ui->reinSB->value();

        this->game->setLevel(this->user->getSavedLevel());

        this->game->newLevelByConfig(ruleN, kind, startR, popN);

        this->close();
    });
}

JumpDialog::~JumpDialog()
{
    delete ui;
}

void JumpDialog::showEvent(QShowEvent *e)
{
    QRect parentRect( parentWidget()->mapToGlobal( QPoint( 0, 0 ) ),
                     parentWidget()->size() );
    move( QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, size(),
                             parentRect ).topLeft() );
}

void JumpDialog::keyPressEvent(QKeyEvent *e)
{
    if (e -> key() == Qt::Key_Escape ||
        e ->key() == Qt::Key_Enter ||
        e->key() == Qt::Key_Return) {
        return;
    }

    QDialog::keyPressEvent(e);
}
