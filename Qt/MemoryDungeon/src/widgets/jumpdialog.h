#ifndef JUMPDIALOG_H
#define JUMPDIALOG_H

#include <QDialog>
#include <QKeyEvent>
#include <QStyle>

#include "../users/user.h"
#include "../gamerules/gamerule.h"

namespace Ui {
class JumpDialog;
}

class JumpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JumpDialog(QWidget *parent, GameRule*, User*);
    ~JumpDialog();

private:
    Ui::JumpDialog *ui;

    User* user;
    GameRule* game;

protected:
    void showEvent(QShowEvent*);
    void keyPressEvent(QKeyEvent*);
};

#endif // JUMPDIALOG_H
