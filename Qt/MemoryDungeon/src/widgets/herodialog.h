#ifndef HERODIALOG_H
#define HERODIALOG_H

#include <QDialog>
#include <QKeyEvent>

#include "../users/user.h"

namespace Ui {
class HeroDialog;
}

class HeroDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HeroDialog(QWidget *parent, User*);
    ~HeroDialog();

private:
    Ui::HeroDialog *ui;

    User* user;

protected:
    void keyPressEvent(QKeyEvent*);
};

#endif // HERODIALOG_H
