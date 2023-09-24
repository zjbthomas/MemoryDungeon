#include "hoverpushbutton.h"

HoverPushButton::HoverPushButton(QWidget *parent) :
    QPushButton(parent)
{

    this->setAttribute(Qt::WA_Hover, true);
}

HoverPushButton::~HoverPushButton()
{

}

void HoverPushButton::enterEvent(QEvent* event) {
    emit enter();
}

void HoverPushButton::leaveEvent(QEvent* event) {
    emit leave();
}
