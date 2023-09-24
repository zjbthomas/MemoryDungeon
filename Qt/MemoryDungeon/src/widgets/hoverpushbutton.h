#ifndef HOVERPUSHBUTTON_H
#define HOVERPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class HoverPushButton;
}

class HoverPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit HoverPushButton(QWidget *parent = nullptr);
    ~HoverPushButton();

signals:
    void enter();
    void leave();

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
};

#endif // HOVERPUSHBUTTON_H
