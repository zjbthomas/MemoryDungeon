#include "clickableprogressbar.h"

ClickableProgressBar::ClickableProgressBar(QWidget *parent) :
    QProgressBar(parent)
{

}

ClickableProgressBar::~ClickableProgressBar()
{

}

void ClickableProgressBar::mousePressEvent(QMouseEvent* event) {
    emit released();
}
