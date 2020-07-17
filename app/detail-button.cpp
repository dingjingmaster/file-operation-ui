#include "detail-button.h"

#include <QDebug>
#include <QPainter>

DetailButton::DetailButton(QWidget *parent) : QWidget(parent)
{

}

void DetailButton::setSize(float size)
{
    if (size > 9) {
        mSize = size;
    }
}

void DetailButton::paintEvent(QPaintEvent *event)
{
    float margin = 2;

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    // draw border
    QPen pen(QColor(0, 0, 0), 1);
    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    float r2 = mSize - 2 * margin;
    painter.save();
    painter.drawEllipse(0, 0, r2, r2);
    painter.restore();

    // draw arch
    painter.save();
    float r26 = r2 / 6;
    float r22 = r2 / 2;
    float m2 = 2 * margin;
    QPoint p1, p2, p3;
    if (!mOpen) {
        p1.setX(r26);
        p1.setY(r22 + m2);

        p2.setX(r22 + 1 / 2 * margin);
        p2.setY(r26 * 2);
        painter.drawLine(p1, p2);

        p3.setX(r26 * 5 + margin);
        p3.setY(r22 + m2);
        painter.drawLine(p2, p3);
    } else {
        p1.setX(r26);
        p1.setY(r22 - m2);

        p2.setX(r22 + 1 / 2 + margin);
        p2.setY(r26 * 4);
        painter.drawLine(p1, p2);

        p3.setX(r26 * 5 + margin);
        p3.setY(r22 - m2);
        painter.drawLine(p2, p3);
    }
    painter.restore();

    Q_UNUSED(event);
}

void DetailButton::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "detail event";
    mOpen = !mOpen;
    update();
}
