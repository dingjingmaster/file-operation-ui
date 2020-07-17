#include "progress-bar.h"

#include <QtMath>
#include <QPainter>

ProgressBar::ProgressBar(QWidget *parent) : QWidget(parent)
{

}

ProgressBar::~ProgressBar()
{

}

void ProgressBar::setArea(QSize size)
{
    mArea = QRectF(10, 10, size.width(), size.height());
    resize(QSize(size.width() + 20, size.height() + 20));
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
    painter.drawRoundedRect(mArea.x(), mArea.y(), mArea.width(), mArea.height(), 1, 1);

    painter.restore();

    // draw background
    painter.save();
    QLinearGradient progressBarBgGradient (QPointF(0, 0), QPointF(0, height()));
    progressBarBgGradient.setColorAt(0.0, QColor(220,220,220));
    progressBarBgGradient.setColorAt(1.0, QColor(211,211,211));

    float margin = 2;

    painter.setPen(Qt::NoPen);
    painter.setBrush(progressBarBgGradient);
    painter.drawRoundedRect(mArea.x() + margin, mArea.y() + margin,
                            mArea.width() - 2 * margin,
                            mArea.height() - 2 * margin, 1, 1);
    painter.restore();

    // draw foreground
    painter.save();
    double value = mCurrentValue * (mArea.width() - mArea.x() - 2 * margin);
    QLinearGradient progressBarfgGradient (QPointF(0, 0), QPointF(0, height()));
    progressBarfgGradient.setColorAt(0.0, QColor(124,252,0));
    progressBarfgGradient.setColorAt(1.0, QColor(127,255,0));
    painter.setPen(Qt::NoPen);
    painter.setBrush(progressBarfgGradient);
    painter.drawRoundedRect(mArea.x() + margin, mArea.y() + margin,
                            mArea.x() + qCeil(value),
                            mArea.height() - 2 * margin, 1, 1);
    painter.restore();

    // draw text
    QRectF textArea = mArea;
    textArea.setWidth(textArea.width() - 2 * margin);
    QFont font = painter.font();
    font.setPixelSize(10);
    painter.setFont(font);
    painter.drawText(textArea, Qt::AlignVCenter | Qt::AlignRight, tr("sudu 200MB/S"));

    Q_UNUSED(event);
}

void ProgressBar::updateValue(double value)
{
    if (value <= 1) {
        mCurrentValue = value;
    }
}
