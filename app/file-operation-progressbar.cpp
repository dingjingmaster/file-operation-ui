#include "file-operation-progressbar.h"

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

FileOperationProgressBar::FileOperationProgressBar(QWidget *parent) : QWidget(parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setContentsMargins(0, 0, 0, 0);

    m_main_layout = new QVBoxLayout(this);
    m_main_layout->setContentsMargins(0, 0, 0, 0);

    m_main_progressbar = new MainProgressBar(nullptr);
    m_other_progressbar = new OtherButton(nullptr);
    m_list_widget = new QListWidget(nullptr);

    m_list_widget->setFrameShape(QListWidget::NoFrame);

    m_main_layout->addWidget(m_main_progressbar);
    m_main_layout->addWidget(m_other_progressbar);
    m_main_layout->addWidget(m_list_widget);
}

void FileOperationProgressBar::mouseMoveEvent(QMouseEvent *event)
{
    if (m_is_press) {
        move(event->globalPos() - m_position);
        event->accept();
    }
}

void FileOperationProgressBar::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button()) {
        m_is_press = true;
        m_position = event->globalPos() - frameGeometry().topLeft();
    }
}

void FileOperationProgressBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_is_press = false;
    }
}


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
        QWidget::mouseMoveEvent(event);
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

    QWidget::mouseReleaseEvent(event);
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
