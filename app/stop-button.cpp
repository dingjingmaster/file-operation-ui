#include "stop-button.h"

#include <QDebug>
#include <QPainter>

StopButton::StopButton(QWidget *parent) : QWidget(parent)
{

}

void StopButton::paintEvent(QPaintEvent *)
{
    float margin = 1.5;

    QPainter painter(this);
    QPen pen(QColor(0, 0, 0), 2);
    painter.setPen(pen);
    QLine line1(QPoint(width() / 2 - 2 * margin, margin), QPoint(width() / 2 - 2 * margin, height() - 2 * margin));
    QLine line2(QPoint(width() / 2 + 2 * margin, margin), QPoint(width() / 2 + 2 * margin, height() - 2 * margin));
    painter.save();
    painter.drawLine(line1);
    painter.restore();
    painter.save();
    painter.drawLine(line2);
    painter.restore();
}

void StopButton::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "stop";
}
