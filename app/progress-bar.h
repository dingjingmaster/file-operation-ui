#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>

class ProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressBar(QWidget *parent = nullptr);
    ~ProgressBar();
    void setArea(QSize size);

protected:
    void paintEvent(QPaintEvent *event) override;

public Q_SLOTS:
    void updateValue(double value);

public:

private:
    QRectF mArea;
    double mCurrentValue;
};

#endif // PROGRESSBAR_H
