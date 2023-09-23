#ifndef USERLOGINDIALOG_H
#define USERLOGINDIALOG_H

#include <QDialog>
#include <QKeyEvent>

#include "messagedialog.h"

#include "../users/user.h"

namespace Ui {
class UserLoginDialog;
}

class UserLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserLoginDialog(QWidget *parent, User*);
    ~UserLoginDialog();

private:
    Ui::UserLoginDialog *ui;

    User* user;

protected:
    void keyPressEvent(QKeyEvent*);
};

#endif // USERLOGINDIALOG_H
