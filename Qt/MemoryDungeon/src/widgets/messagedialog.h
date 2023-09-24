#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDebug>

#include <QDialog>
#include <QKeyEvent>
#include <QStyle>

#include <QTimer>

#include <QMovie>

#include <QTransform>

#include <string>

#include "../users/user.h"

#include "clickablelabel.h"

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
    void repaintLbl();

    Ui::MessageDialog *ui;

    User* user;
    bool useAnimated;

    bool isNewKind;
    string gachaPath;

    ClickableLabel* animatedLbl;
    int x = 0;
    int cycle = 1;

    QTimer* timer;

protected:
    void showEvent(QShowEvent*);
    void keyPressEvent(QKeyEvent*);
};

#endif // MESSAGEDIALOG_H
