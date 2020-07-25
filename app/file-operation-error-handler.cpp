#include "file-operation-error-handler.h"

#include <QPainter>


FileOperationErrorHandler::FileOperationErrorHandler(QDialog *parent) : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setContentsMargins(0, 0, 0, 0);
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

FileConflictDialog::FileConflictDialog(QDialog *parent) : FileOperationErrorHandler(parent)
{
    setFixedSize(m_fix_width, m_fix_height);
}

void FileConflictDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    paintHeader(painter);
    paintContent(painter);

    Q_UNUSED(event);
}

void FileConflictDialog::paintHeader(QPainter &painter)
{
    painter.save();

    // paint title
    QRect textArea (m_title_margin_left, 0, m_title_width, m_header_height);
    QFont font = painter.font();
    font.setPixelSize(10);
    painter.setFont(font);
    painter.drawText(textArea, Qt::AlignVCenter | Qt::AlignLeft, m_title_text);

    // paint minilize button
    QPen pen(QColor(192,192,192), 1);
    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawRect(m_fix_width - m_margin * 2 - m_btn_size * 2, m_margin, m_btn_size, m_btn_size);

    // paint close button
    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawRect(m_fix_width - m_margin - m_btn_size, m_margin, m_btn_size, m_btn_size);

    // paint content text
    painter.drawRect(m_text_margin_left, m_text_margin_top, width() - m_text_margin_left - m_margin_lr, m_text_height);
    painter.restore();
}

void FileConflictDialog::paintContent(QPainter &painter)
{
    painter.save();
    QPen pen(QColor(192,192,192), 1);
    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawRect(m_margin_lr, m_ct1_margin_top, width() - 2 * m_margin_lr, m_ct1_heigth);

    pen.setStyle(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawRect(m_margin_lr, m_ct2_margin_top, width() - 2 * m_margin_lr, m_ct2_heigth);
    painter.restore();
}

FileOperationErrorHandler::ResponseInfo *FileConflictDialog::packResult(int ret)
{

}
