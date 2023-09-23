#ifndef SHOPDIALOG_H
#define SHOPDIALOG_H

#include <QDialog>
#include <QKeyEvent>

#include "../users/user.h"

namespace Ui {
class ShopDialog;
}

class ShopDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShopDialog(QWidget *parent, User*);
    ~ShopDialog();

private:
    Ui::ShopDialog *ui;

    User* user;

protected:
    void keyPressEvent(QKeyEvent*);
};

#endif // SHOPDIALOG_H
