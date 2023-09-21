#include "userlogindialog.h"
#include "ui_userlogindialog.h"

UserLoginDialog::UserLoginDialog(QWidget *parent, User* user) :
    QDialog(parent),
    ui(new Ui::UserLoginDialog)
{
    ui->setupUi(this);

    setWindowFlags( Qt::CustomizeWindowHint | Qt::Dialog);

    this->setFixedSize(520, 712);

    this->user = user;

    connect(ui->loginBtn, &QPushButton::released, this, [=]() {
        string username = ui->usernameLE->text().toStdString();

        if (username == "") {
            MessageDialog* messageDialog = new MessageDialog(this, "Please input a valid username!", "Error", false, this->user);
            messageDialog->setModal(true);
            messageDialog->exec();
            delete messageDialog;

            return;
        }

        string password = ui->passwordLE->text().toStdString();

        int check = this->user->readFile(username, password);
        if (check == -1) {
            for (int k = 0; k < 5; k++) { // TODO: magic number: initial number of normal kinds
                user->setAnOwnedK(k, true);
            }
            for (int sp = 0; sp < 6; sp++) { // TODO: magic number: initial number of special kinds
                user->setAnOwnedSp(sp, true);
            }

            string welcomeMsg = "Welcome " + username + "!\nThis is your first time to the dungeon.\nWe have marked down your name on our list.\nHope you find your memory back!";
            MessageDialog* messageDialog = new MessageDialog(this, welcomeMsg, "A New Finder!", false, this->user);
            messageDialog->setModal(true);
            messageDialog->exec();
            delete messageDialog;
        } else {
            if (check == -2) {
                string msg = "Password wrong!\nYou are not allowed to get into the dungeon!";
                MessageDialog* messageDialog = new MessageDialog(this, msg, "Error", false, this->user);
                messageDialog->setModal(true);
                messageDialog->exec();
                delete messageDialog;

                return;
            } else {
                string welcomeMsg = "Welcome back to the dungeon, " + username + "!";
                MessageDialog* messageDialog = new MessageDialog(this, welcomeMsg, "Welcome back!", false, this->user);
                messageDialog->setModal(true);
                messageDialog->exec();
                delete messageDialog;
            }
        }

        this->close();
    });
}

UserLoginDialog::~UserLoginDialog()
{
    delete ui;
}
