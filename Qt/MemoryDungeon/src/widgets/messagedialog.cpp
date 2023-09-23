#include "messagedialog.h"
#include "ui_messagedialog.h"

MessageDialog::MessageDialog(QWidget *parent, string msg, string title, bool useImg, User* user) :
    QDialog(parent),
    ui(new Ui::MessageDialog)
{
    // TODO: if useImg is true

    ui->setupUi(this);

    setWindowFlags( Qt::FramelessWindowHint | Qt::Dialog);

    this->setFixedSize(539, 393);

    ui->titleLbl->setText(QString::fromStdString(title));
    ui->msgTB->setText(QString::fromStdString(msg));

    this->useImg = useImg;

    this->user = user;

    connect(ui->okBtn, &QPushButton::released, this, [=]() {
        this->close();
    });
}

MessageDialog::~MessageDialog()
{
    delete ui;
}

void MessageDialog::keyPressEvent(QKeyEvent *e)
{
    if (e -> key() == Qt::Key_Escape ||
        e ->key() == Qt::Key_Enter ||
        e->key() == Qt::Key_Return) {
        return;
    }

    QDialog::keyPressEvent(e);
}
