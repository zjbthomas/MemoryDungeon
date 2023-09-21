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

private:
    int pos = -1;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CLICKABLELABEL_H
