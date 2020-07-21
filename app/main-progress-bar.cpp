#include "main-progress-bar.h"

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>


MainProgressBar::MainProgressBar(QWidget *parent) : QWidget(parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setMouseTracking(true);

    m_title = "sadasudianhdiahdisahud";

    setFixedSize(m_fix_width, m_fix_height);
}

void MainProgressBar::paintEvent(QPaintEvent *event)
{
    QPainter painter (this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    paintProgress (painter);
    paintHeader (painter);
    paintFoot (painter);
    paintContent (painter);

    Q_UNUSED(event);
}

void MainProgressBar::mouseMoveEvent(QMouseEvent *event)
{
    // minilize button
    QPoint pos = event->pos();
    if ((pos.x() >= m_fix_width - m_btn_margin * 2 - m_btn_size * 2)
            && (pos.x() <= (m_fix_width - m_btn_margin * 2 - m_btn_size))
            && (pos.y() >= m_btn_margin_top)
            && (pos.y() <= m_btn_margin_top + m_btn_size)) {
        setCursor(Qt::PointingHandCursor);
    } else if ((pos.x() >= m_fix_width - m_btn_margin - m_btn_size)
               && (pos.x() <= (m_fix_width - m_btn_margin))
               && (pos.y() >= m_btn_margin_top)
               && (pos.y() <= m_btn_margin_top + m_btn_size)) {
        setCursor(Qt::PointingHandCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
}

void MainProgressBar::mouseReleaseEvent(QMouseEvent *event)
{
    // minilize button
    QPoint pos = event->pos();
    if ((pos.x() >= m_fix_width - m_btn_margin * 2 - m_btn_size * 2)
            && (pos.x() <= (m_fix_width - m_btn_margin * 2 - m_btn_size))
            && (pos.y() >= m_btn_margin_top)
            && (pos.y() <= m_btn_margin_top + m_btn_size)) {
        qDebug() << "mini";
    } else if ((pos.x() >= m_fix_width - m_btn_margin - m_btn_size)
               && (pos.x() <= (m_fix_width - m_btn_margin))
               && (pos.y() >= m_btn_margin_top)
               && (pos.y() <= m_btn_margin_top + m_btn_size)) {
        qDebug() << "close";
    }
}

void MainProgressBar::paintFoot(QPainter &painter)
{
    painter.save();

    double value = m_current_value * m_fix_width;
    QLinearGradient progressBarBgGradient (QPointF(0, 0), QPointF(0, height()));
    progressBarBgGradient.setColorAt(0.0, QColor(75,0,130));
    progressBarBgGradient.setColorAt(1.0, QColor(75,0,130));
    painter.setPen(Qt::NoPen);
    painter.setBrush(progressBarBgGradient);
    painter.drawRoundedRect(0, m_fix_height - m_foot_margin, value, m_foot_margin, 1, 1);

    painter.restore();
}

void MainProgressBar::paintHeader(QPainter &painter)
{
    painter.save();

    // paint title
    QRect textArea (0, 0, m_title_width, m_header_height);
    QFont font = painter.font();
    font.setPixelSize(10);
    painter.setFont(font);
    painter.drawText(textArea, Qt::AlignVCenter | Qt::AlignHCenter, m_title);

    // paint minilize button
    QPen pen(QColor(192,192,192), 1);
    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawRect(m_fix_width - m_btn_margin * 2 - m_btn_size * 2, m_btn_margin_top, m_btn_size, m_btn_size);

    // paint close button
    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawRect(m_fix_width - m_btn_margin - m_btn_size, m_btn_margin_top, m_btn_size, m_btn_size);

    painter.restore();
}

void MainProgressBar::paintContent(QPainter &painter)
{
    double x = 0;
    double y = 0;
    double w = 0;
    double h = 0;

    painter.save();

    // paint icon
    QPen pen(QColor(192,192,192), 1);
    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    y = m_fix_height / 2 - m_icon_size / 2;
    painter.drawRect(m_icon_margin, y, m_icon_size, m_icon_size);

    // paint file name
    x = m_icon_margin + m_file_name_margin + m_icon_size;
    y = m_fix_height / 2 - m_file_name_height / 2;
    w = m_fix_width - m_icon_size - m_icon_margin - m_file_name_margin * 3;
    painter.drawRect(x, y, w, m_file_name_height);

    // paint percentage
    x = m_fix_width - m_percent_margin * 3;
    y = m_fix_height - m_foot_margin - m_percent_height - m_percent_margin;
    w = m_percent_margin * 2;
    painter.drawRect(x, y, w, m_percent_height);


    painter.restore();
}

void MainProgressBar::paintProgress(QPainter &painter)
{
    painter.save();

    double value = m_current_value * m_fix_width;
    QLinearGradient progressBarBgGradient (QPointF(0, 0), QPointF(0, height()));
    progressBarBgGradient.setColorAt(0.0, QColor(175,238,238));
    progressBarBgGradient.setColorAt(1.0, QColor(175,238,238));
    painter.setPen(Qt::NoPen);
    painter.setBrush(progressBarBgGradient);
    painter.drawRoundedRect(0, 0, value, m_fix_height, 1, 1);

    painter.restore();
}


