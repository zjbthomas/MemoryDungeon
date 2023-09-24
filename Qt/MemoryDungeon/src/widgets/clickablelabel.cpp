#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent = nullptr, int pos = -1) :
    QLabel(parent)
{
    this->pos = pos;
}

ClickableLabel::~ClickableLabel()
{

}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    if (this->isClickable) {
        emit released();
    }
}

int ClickableLabel::getPos() {
    return this->pos;
}

void ClickableLabel::setIsClickable(bool c) {
    this->isClickable = c;
}
