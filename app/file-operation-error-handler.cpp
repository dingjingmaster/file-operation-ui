#include "file-operation-error-handler.h"

#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>

QPushButton* btn;

static QPixmap drawSymbolicColoredPixmap (const QPixmap& source);

FileOperationErrorHandler::FileOperationErrorHandler(QDialog *parent) : BaseWidget(parent)
{
    btn = new QPushButton;
}

FileOperationErrorHandler::~FileOperationErrorHandler()
{

}

FileOperationErrorHandler::ResponseInfo *FileOperationErrorHandler::handleError(const QString &srcUri, const QString &destDirUri, const GError* err, bool isCritical)
{
    setSrcUri(srcUri);
    setDestUri(destDirUri);
    if (nullptr != err) {
        setErrorString(err->message);
    }
    m_is_critical = isCritical;
    return packResult(exec());
}

bool FileOperationErrorHandler::getCritical()
{
    return m_is_critical;
}

void FileOperationErrorHandler::setSrcUri(QString uri)
{
    m_src_uri = uri;
}

void FileOperationErrorHandler::setDestUri(QString uri)
{
    m_dest_uri = uri;
}

void FileOperationErrorHandler::setCritical(bool critical)
{
    m_is_critical = critical;
}

void FileOperationErrorHandler::setErrorString(QString str)
{
    m_error_string = str;
}

QString FileOperationErrorHandler::getSrcUri()
{
    return m_src_uri;
}

QString FileOperationErrorHandler::getDestUri()
{
    return m_dest_uri;
}

QString FileOperationErrorHandler::getErrorString()
{
    return m_error_string;
}

bool FileOperationErrorHandler::getDoSimilar()
{
    return m_do_similar;
}

void FileOperationErrorHandler::setDoSimilar(bool sim)
{
    m_do_similar = sim;
}

FileConflictDialog::FileConflictDialog(QDialog *parent) : FileOperationErrorHandler(parent)
{
    setFixedSize(m_fix_width, m_fix_height);
    setContentsMargins(9, 9, 9, 9);

    m_tip = new QLabel(this);
    m_tip->setBackgroundRole(QPalette::Link);
    m_tip->setFrameStyle(2);
    m_tip->setGeometry(m_margin_lr, m_tip_y, width() - 2 * m_margin_lr, m_tip_height);

    m_file_label1 = new FileInformationLabel(this);
    m_file_label1->setGeometry(m_margin_lr, m_file_info1_top, width() - 2 * m_margin_lr, m_file_info_height);

    m_file_label2 = new FileInformationLabel(this);
    m_file_label2->setGeometry(m_margin_lr, m_file_info2_top, width() - 2 * m_margin_lr, m_file_info_height);

    m_ck_box = new QCheckBox(this);
    m_ck_box->setGeometry(m_margin_lr, m_ck_btn_top, m_ck_btn_heigth, m_ck_btn_heigth);

    m_rename = new QPushButton(this);
    m_rename->setGeometry(m_margin_lr, m_btn_top, m_btn_width, m_btn_heigth);

    m_cancel = new QPushButton(this);
    m_cancel->setGeometry(m_btn_cancel_margin_left, m_btn_top, m_btn_width, m_btn_heigth);

    m_ok = new QPushButton(this);
    m_ok->setGeometry(m_btn_ok_margin_left, m_btn_top, m_btn_width, m_btn_heigth);
}

FileConflictDialog::~FileConflictDialog()
{

}

FileOperationErrorHandler::ResponseInfo *FileConflictDialog::packResult(int ret)
{

}

FileInformationLabel::FileInformationLabel(QWidget *parent) : QWidget(parent)
{
    setFixedSize(m_fix_width, m_fix_heigth);
    setContentsMargins(0, 0, 0, 0);
}

RenameDialog::RenameDialog(QWidget *parent) : BaseWidget(parent)
{

}

RenameDialog::~RenameDialog()
{

}

static QPixmap drawSymbolicColoredPixmap (const QPixmap& source)
{
    // 18, 32, 69
    QColor baseColor = btn->palette().color(QPalette::Text).light(150);
    QImage img = source.toImage();

    for (int x = 0; x < img.width(); ++x) {
        for (int y = 0; y < img.height(); ++y) {
            auto color = img.pixelColor(x, y);
            color.setRed(baseColor.red());
            color.setGreen(baseColor.green());
            color.setBlue(baseColor.blue());
            img.setPixelColor(x, y, color);
        }
    }

    return QPixmap::fromImage(img);
}

BaseWidget::BaseWidget(QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    setContentsMargins(0, 0, 0, 0);
}

void BaseWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.save();

    // paint title
    QRect textArea (m_margin_lr, m_margin_tp, width() - m_margin_lr * 2 - 2 * m_btn_size, m_header_height);
    QFont font = painter.font();
    font.setPixelSize(10);
    painter.setFont(font);
    painter.drawText(textArea, Qt::AlignVCenter | Qt::AlignHCenter, m_title);

    // paint minilize button
    QPen pen(QColor(192,192,192), 1);
    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawPixmap(width() - m_margin_lr * 2 - m_btn_size * 2, m_margin_tp, m_btn_size, m_btn_size,
                           drawSymbolicColoredPixmap(QIcon::fromTheme("window-minimize-symbolic").pixmap(m_btn_size, m_btn_size)));

    // paint close button
    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawPixmap(width() - m_margin_lr - m_btn_size, m_margin_tp, m_btn_size, m_btn_size,
                           drawSymbolicColoredPixmap(QIcon::fromTheme("window-close-symbolic").pixmap(m_btn_size, m_btn_size)));

    painter.restore();
}

void BaseWidget::mouseMoveEvent(QMouseEvent *event)
{
    // minilize button
    QPoint pos = event->pos();
    if ((pos.x() >= width() - m_margin_lr * 2 - m_btn_size * 2)
            && (pos.x() <= width() - m_margin_lr * 2 - m_btn_size)
            && (pos.y() >= m_margin_tp)
            && (pos.y() <= m_margin_tp + m_btn_size)) {
        setCursor(Qt::PointingHandCursor);
    } else if ((pos.x() >= width() - m_margin_lr - m_btn_size)
               && (pos.x() <= width() - m_margin_lr)
               && (pos.y() >= m_margin_tp)
               && (pos.y() <= m_margin_tp + m_btn_size)) {
        setCursor(Qt::PointingHandCursor);
    } else {
        setCursor(Qt::ArrowCursor);
        QWidget::mouseMoveEvent(event);
    }
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event)
{
    // minilize button
    QPoint pos = event->pos();
    if ((pos.x() >= width() - m_margin_lr * 2 - m_btn_size * 2)
            && (pos.x() <= width() - m_margin_lr * 2 - m_btn_size)
            && (pos.y() >= m_margin_tp)
            && (pos.y() <= m_margin_tp + m_btn_size)) {
        Q_EMIT showMinimized();
    } else if ((pos.x() >= width() - m_margin_lr - m_btn_size)
               && (pos.x() <= width() - m_margin_lr)
               && (pos.y() >= m_margin_tp)
               && (pos.y() <= m_margin_tp + m_btn_size)) {
        close();
    }

    QWidget::mouseReleaseEvent(event);
}
