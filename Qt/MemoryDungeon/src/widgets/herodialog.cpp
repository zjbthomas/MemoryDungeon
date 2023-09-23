#include "herodialog.h"
#include "ui_herodialog.h"

HeroDialog::HeroDialog(QWidget *parent, User* user) :
    QDialog(parent),
    ui(new Ui::HeroDialog)
{
    ui->setupUi(this);

    setWindowFlags( Qt::FramelessWindowHint | Qt::Dialog);

    this->user = user;
}

HeroDialog::~HeroDialog()
{
    delete ui;
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
