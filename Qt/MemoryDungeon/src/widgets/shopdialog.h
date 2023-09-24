#ifndef SHOPDIALOG_H
#define SHOPDIALOG_H

#include <QDialog>
#include <QKeyEvent>
#include <QStyle>

#include <QTimer>

#include <QMovie>

#include "../users/user.h"

#include "clickablelabel.h"
#include "messagedialog.h"

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
    void repaintLbl();

    Ui::ShopDialog *ui;

    User* user;

    bool isNewKind;
    bool hasGift = false;
    string gachaPath;

    int x = 0;
    int cycle = 1;
    int price = 10;

    QTimer* timer;

    ClickableLabel* activeLbl;

protected:
    void showEvent(QShowEvent*);
    void keyPressEvent(QKeyEvent*);
};

#endif // SHOPDIALOG_H
