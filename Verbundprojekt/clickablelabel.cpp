#include "clickablelabel.h"
#include <QPainter>


ClickableLabel::ClickableLabel(QWidget *parent, Qt::WindowFlags f) : QLabel(parent)
{

}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {

    emit clicked(id);
    this->objectName();
}
