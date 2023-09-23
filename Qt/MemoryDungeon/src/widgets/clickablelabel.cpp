#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent, int pos) :
    QLabel(parent)
{
    this->pos = pos;
}

ClickableLabel::~ClickableLabel()
{

}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    emit released();
}

int ClickableLabel::getPos() {
    return this->pos;
}