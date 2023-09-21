#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>

#include <string>

#include "../users/user.h"

namespace Ui {
class MessageDialog;
}

class MessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MessageDialog(QWidget *parent, string, string, bool, User*);
    ~MessageDialog();

private:
    Ui::MessageDialog *ui;

    User* user;
    bool useImg;
};

#endif // MESSAGEDIALOG_H
