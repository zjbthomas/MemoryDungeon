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
}

JumpDialog::~JumpDialog()
{
    delete ui;
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
