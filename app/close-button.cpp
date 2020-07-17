#include "close-button.h"

#include <QDebug>
#include <QPainter>

CloseButton::CloseButton(QWidget *parent) : QPushButton(parent)
{
    resize(30, 30);
}

void CloseButton::paintEvent(QPaintEvent *)
{
    float margin = 2;

    QPainter painter(this);
    QPen pen(QColor(0, 0, 0), 2);
    painter.setPen(pen);
    QLine line1(QPoint(margin, margin), QPoint(this->width() - 2 * margin, this->height() - 2 * margin));
    QLine line2(QPoint(margin, this->height() - 2 * margin), QPoint(this->width() - 2 * margin, margin));
    painter.save();
    painter.drawLine(line1);
    painter.restore();
    painter.save();
    painter.drawLine(line2);
    painter.restore();
}

void CloseButton::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "click";
}
