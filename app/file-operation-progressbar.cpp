#include "file-operation-progressbar.h"

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

FileOperationProgressBar *FileOperationProgressBar::getInstance()
{
    static FileOperationProgressBar fb;

    return &fb;
}

ProgressBar *FileOperationProgressBar::addFileOperation()
{
    ProgressBar* proc = new ProgressBar;
    QListWidgetItem* li = new QListWidgetItem(m_list_widget);
    m_list_widget->addItem(li);
    m_list_widget->setItemWidget(li, proc);
    (*m_progress_list)[proc] = li;
    li->setSizeHint(QSize(m_main_progressbar->width(), m_progress_item_height));

    li->setFlags(Qt::NoItemFlags);

    connect(proc, &ProgressBar::finished, this, &FileOperationProgressBar::removeFileOperation);
    ++ m_progress_size;

    showMore();

    return proc;
}

void FileOperationProgressBar::showProgress(ProgressBar &progress)
{
    // check Main progress is inuse???
}

void FileOperationProgressBar::removeFileOperation(ProgressBar *progress)
{
    showMore();
}

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

    m_progress_list = new QMap<ProgressBar*, QListWidgetItem*>;

    showWidgetList(false);

    connect(m_main_progressbar, &MainProgressBar::minimized, [=](){
        this->showMinimized();
    });
    connect(m_main_progressbar, &MainProgressBar::closeWindow, [=](){
        qDebug() << "close all";
        Q_EMIT cancelAll();
    });
    connect(m_other_progressbar, &OtherButton::clicked, this, &FileOperationProgressBar::showWidgetList);

    showMore();
}

void FileOperationProgressBar::showMore()
{
    if (m_progress_size > 1) {
        m_other_progressbar->show();
    } else {
        m_other_progressbar->hide();
    }

    if (m_progress_size > 1 && m_progress_size <= m_show_items) {
        m_list_widget->setFixedHeight(m_progress_size * m_progress_item_height);
    } else if (m_progress_size > 3) {
        m_list_widget->setFixedHeight(3 * m_progress_item_height);
    }

    if (m_show_more) {
        qDebug() << "show more: " << m_show_more << " w: " << width() << " h: " << height();
        setFixedSize(m_main_progressbar->width(), m_main_progressbar->height() + m_other_progressbar->height() + m_list_widget->height());
    } else {
        qDebug() << "show little: " << m_show_more << " w: " << width() << " h: " << height();
        setFixedSize(m_main_progressbar->width(), m_main_progressbar->height() + m_other_progressbar->height());
    }

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

void FileOperationProgressBar::showWidgetList(bool show)
{
    m_show_more = show;
    if (show) {
        m_list_widget->show();
    } else {
        m_list_widget->hide();
    }
    showMore();
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
        Q_EMIT minimized();
    } else if ((pos.x() >= m_fix_width - m_btn_margin - m_btn_size)
               && (pos.x() <= (m_fix_width - m_btn_margin))
               && (pos.y() >= m_btn_margin_top)
               && (pos.y() <= m_btn_margin_top + m_btn_size)) {
        Q_EMIT closeWindow();
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

void MainProgressBar::updateValue(double)
{

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
    m_show = !m_show;

    Q_EMIT clicked(m_show);

    Q_UNUSED(event);
}

ProgressBar::ProgressBar(QWidget *parent) : QWidget(parent)
{
    setContentsMargins(0, 0, 0, 0);
    setFixedHeight(m_fix_height);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

ProgressBar::~ProgressBar()
{

}

void ProgressBar::initParam()
{

}

void ProgressBar::paintEvent(QPaintEvent *event)
{
    double x = 0;
    double y = 0;
    double w = 0;
    double h = 0;

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    painter.save();

    // paint icon
    x = m_margin_lr;
    y = (height() - m_margin_ud * 2 - m_icon_size) / 2 + m_margin_ud;
    QPen pen(QColor(192, 192, 192), 1);
    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawRect(x, y, m_icon_size, m_icon_size);

    // paint text
    x = m_margin_lr * 2 + m_icon_size;
    y = (height() - m_margin_ud * 2 - m_text_height) / 2 + m_margin_ud;
    w = width() - m_margin_lr * 5 - m_icon_size - m_btn_size - m_progress_width - m_percent_width;
    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawRect(x, y, w, m_text_height);

    // paint progress
    x = m_margin_lr * 3 + m_icon_size + w;
    y = (height() - m_margin_ud * 2 - m_progress_height) / 2 + m_margin_ud;

    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawRect(x, y, m_progress_width, m_progress_height);

    // paint close
    x =  m_margin_lr * 4 + m_icon_size + w + m_progress_width;
    y = (height() - m_margin_ud * 2 - m_percent_width) / 2 + m_margin_ud;

    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawRect(x, y, m_percent_width, m_percent_width);

    painter.restore();
}
