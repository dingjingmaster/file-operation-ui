#include "other-button.h"

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

OtherButton::OtherButton(QWidget *parent) : QWidget(parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setMouseTracking(true);
    setMinimumWidth(180);
    setFixedHeight(m_button_heigth);
    setContentsMargins(0, 0, 0, 0);
}

void OtherButton::paintEvent(QPaintEvent *event)
{
    double x = 0;
    double y = 0;
    double w = 0;
    double h = 0;

    QPainter painter(this);
    painter.save();
    QPen pen(QColor(192,192,192), 1);
    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);

    // paint icon
    x = width() / 2 - m_icon_size - m_icon_margin - 20;
    y = (m_button_heigth - m_icon_size) / 2;
    QRect iconArea (x, y, m_icon_size, m_icon_size);
    painter.drawRect(iconArea);

    // paint text
    x = x + m_icon_size + 10;
    m_text = "dsadadadsada";
    QRect textArea (x, 0, m_text_length, m_button_heigth);
    QFont font = painter.font();
    font.setPixelSize(10);
    painter.setFont(font);
    painter.drawText(textArea, Qt::AlignLeft | Qt::AlignVCenter, m_text);

    painter.restore();

    Q_UNUSED(event);
}

void OtherButton::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "click!";
}
