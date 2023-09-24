#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QWidget>
#include <QLabel>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent, int);
    ~ClickableLabel();

    int getPos();

    void setIsClickable(bool);

private:
    int pos = -1;

    bool isClickable = true;

signals:
    void released();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CLICKABLELABEL_H
