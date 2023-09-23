#include "shopdialog.h"
#include "ui_shopdialog.h"

ShopDialog::ShopDialog(QWidget *parent, User* user) :
    QDialog(parent),
    ui(new Ui::ShopDialog)
{
    ui->setupUi(this);

    setWindowFlags( Qt::FramelessWindowHint | Qt::Dialog);

    this->user = user;
}

ShopDialog::~ShopDialog()
{
    delete ui;
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
