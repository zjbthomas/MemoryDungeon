#ifndef COLLECTIONDIALOG_H
#define COLLECTIONDIALOG_H

#include <QDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QStyle>

#include "qmovie.h"

#include "../users/user.h"

namespace Ui {
class CollectionDialog;
}

class CollectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CollectionDialog(QWidget *parent, User*, int, int, int);
    ~CollectionDialog();

private:
    Ui::CollectionDialog *ui;

    User* user;
    int maxK;
    int maxSp;
    int offset;

    int curPos;

    QLabel** cardLblArr;
    QLabel** indexLblArr;


protected:
    void updateShowcase();

    void showEvent(QShowEvent*);
    void keyPressEvent(QKeyEvent*);
};

#endif // COLLECTIONDIALOG_H
