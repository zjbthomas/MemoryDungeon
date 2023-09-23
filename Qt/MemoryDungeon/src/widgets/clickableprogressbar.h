#ifndef CLICKABLEPROGRESSBAR_H
#define CLICKABLEPROGRESSBAR_H

#include <QWidget>
#include <QProgressBar>

namespace Ui {
class ClickableProgressBar;
}

class ClickableProgressBar : public QProgressBar
{
    Q_OBJECT

public:
    explicit ClickableProgressBar(QWidget *parent = nullptr);
    ~ClickableProgressBar();

signals:
    void released();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CLICKABLEPROGRESSBAR_H
