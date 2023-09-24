#ifndef HERODIALOG_H
#define HERODIALOG_H

#include <QDialog>
#include <QKeyEvent>
#include <QPushButton>
#include <QStyle>

#include "../users/user.h"

#include "hoverpushbutton.h"

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

protected:
    void showEvent(QShowEvent*);
    void keyPressEvent(QKeyEvent*);
};

#endif // HERODIALOG_H
