#include "file-operation-process-bar.h"

#include <QDebug>
#include <QtMath>
#include <QPainter>

FileOperationProcessBar & FileOperationProcessBar::getInstance()
{
    static FileOperationProcessBar fp;

    return fp;
}

FileOperationProcess &FileOperationProcessBar::addFileOperation()
{
    FileOperationProcess* opc = new FileOperationProcess(nullptr);
    m_detail_layout->addWidget(opc);

    update();
    return *opc;
}

void FileOperationProcessBar::openDetail(bool open)
{
    if (open) {
        m_detail_label->setText(tr("display details"));
    } else {
        m_detail_label->setText(tr("display brief"));
    }

    m_detail_open = open;
}

FileOperationProcessBar::FileOperationProcessBar(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(m_width, m_height);
    setMaximumHeight(m_max_height);

    m_detail_label = new QLabel(nullptr);
    m_main_layout = new QVBoxLayout(nullptr);
    m_show_detail = new DetailButton(nullptr);
    m_detail_layout = new QHBoxLayout(nullptr);
    m_process_layout = new QVBoxLayout(nullptr);
    m_process = new QMap<FileOperationProcess, Status>();

    m_detail_label->setMargin(0);

    openDetail(m_detail_open);

    m_detail_layout->addWidget(m_show_detail);
    m_detail_layout->addWidget(m_detail_label);

    m_main_layout->addLayout(m_process_layout);
    m_main_layout->addLayout(m_detail_layout);

    setLayout(m_main_layout);

    connect (m_show_detail, &DetailButton::valueChanged, this, &FileOperationProcessBar::openDetail);
}

FileOperationProcessBar::~FileOperationProcessBar()
{
    // FIXME://
    delete m_process;
    delete m_show_detail;
    delete m_main_layout;
    delete m_process_layout;
}

DetailButton::DetailButton(QWidget *parent) : QWidget(parent)
{

}

void DetailButton::setSize(float size)
{
    if (size > 9) {
        m_size = size;
    }
}

void DetailButton::paintEvent(QPaintEvent *event)
{
    m_size = 20;
    float margin = m_size / 10;

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    // draw border
    QPen pen(QColor(0, 0, 0), 1);
    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    float r2 = m_size - 2 * margin;
    painter.save();
    painter.drawEllipse(margin, margin, r2, r2);
    painter.restore();

    // draw arch
    painter.save();
    float r28 = r2 / 8;
    QPoint p1, p2, p3;
    if (!m_open) {
        p1.setX(r28 + margin);
        p1.setY(r28 * 6);

        p2.setX(r28 * 4 + margin);
        p2.setY(r28 * 4);
        painter.drawLine(p1, p2);

        p3.setX(r28 * 7 + margin);
        p3.setY(r28 * 6);
        painter.drawLine(p2, p3);
    } else {
        p1.setX(r28 + margin);
        p1.setY(r28 * 4);

        p2.setX(r28 * 4 + margin);
        p2.setY(r28 * 6);
        painter.drawLine(p1, p2);

        p3.setX(r28 * 7 + margin);
        p3.setY(r28 * 4);
        painter.drawLine(p2, p3);
    }
    painter.restore();

    Q_UNUSED(event);
}

void DetailButton::mouseReleaseEvent(QMouseEvent *event)
{
    m_open = !m_open;

    Q_EMIT valueChanged(m_open);

    update();

    Q_UNUSED(event);
}


StartStopButton::StartStopButton(QWidget *parent) : QWidget(parent)
{

}

void StartStopButton::paintEvent(QPaintEvent *)
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

void StartStopButton::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "stop";
}

CloseButton::CloseButton(QWidget *parent) : QWidget(parent)
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

    Q_UNUSED(event);
}

FileOperationProcess::FileOperationProcess(QWidget *parent) : QWidget(parent)
{
    m_close = new CloseButton(nullptr);
    m_process_name = new QLabel(nullptr);
    m_process_file = new QLabel(nullptr);
    m_progress = new ProgressBar(nullptr);
    m_process_percent = new QLabel(nullptr);
    m_vbox_layout = new QVBoxLayout(nullptr);
    m_main_layout = new QHBoxLayout(nullptr);
    m_process_left_item = new QLabel(nullptr);
    m_start_stop = new StartStopButton(nullptr);

    m_process_name->setText("dasdsada");

    m_vbox_layout->addWidget(m_process_percent);
    m_vbox_layout->addWidget(m_start_stop);
    m_vbox_layout->addWidget(m_close);

    m_main_layout->addWidget(m_process_name);
    m_main_layout->addLayout(m_vbox_layout);
    m_main_layout->addWidget(m_progress);
    m_main_layout->addWidget(m_process_file);
    m_main_layout->addWidget(m_process_left_item);

    setLayout(m_main_layout);
}

FileOperationProcess::~FileOperationProcess()
{
    delete m_close;
    delete m_progress;
    delete m_start_stop;
    delete m_process_name;
    delete m_process_file;
    delete m_process_percent;
    delete m_process_left_item;

    delete m_vbox_layout;
    delete m_main_layout;
}

void FileOperationProcess::showDetail(bool detail)
{
    m_show_detail = detail;
    update();
}

ProgressBar::ProgressBar(QWidget *parent)
{

}

ProgressBar::~ProgressBar()
{

}

void ProgressBar::setArea(QSize size)
{

}

void ProgressBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

        // draw border
        painter.save();
        QPen pen(QColor(192,192,192), 1);
        pen.setStyle(Qt::SolidLine);
        painter.setBrush(Qt::NoBrush);
        painter.setPen(pen);
        painter.drawRoundedRect(m_area.x(), m_area.y(), m_area.width(), m_area.height(), 1, 1);

        painter.restore();

        // draw background
        painter.save();
        QLinearGradient progressBarBgGradient (QPointF(0, 0), QPointF(0, height()));
        progressBarBgGradient.setColorAt(0.0, QColor(220,220,220));
        progressBarBgGradient.setColorAt(1.0, QColor(211,211,211));

        float margin = 2;

        painter.setPen(Qt::NoPen);
        painter.setBrush(progressBarBgGradient);
        painter.drawRoundedRect(m_area.x() + margin, m_area.y() + margin,
                                m_area.width() - 2 * margin,
                                m_area.height() - 2 * margin, 1, 1);
        painter.restore();

        // draw foreground
        painter.save();
        double value = m_current_value * (m_area.width() - m_area.x() - 2 * margin);
        QLinearGradient progressBarfgGradient (QPointF(0, 0), QPointF(0, height()));
        progressBarfgGradient.setColorAt(0.0, QColor(124,252,0));
        progressBarfgGradient.setColorAt(1.0, QColor(127,255,0));
        painter.setPen(Qt::NoPen);
        painter.setBrush(progressBarfgGradient);
        painter.drawRoundedRect(m_area.x() + margin, m_area.y() + margin,
                                m_area.x() + qCeil(value),
                                m_area.height() - 2 * margin, 1, 1);
        painter.restore();

        // draw text
        QRectF textArea = m_area;
        textArea.setWidth(textArea.width() - 2 * margin);
        QFont font = painter.font();
        font.setPixelSize(10);
        painter.setFont(font);
        painter.drawText(textArea, Qt::AlignVCenter | Qt::AlignRight, tr("sudu 200MB/S"));

        Q_UNUSED(event);
}

void ProgressBar::updateValue(double value)
{

}
