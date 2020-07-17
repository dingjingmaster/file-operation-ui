#ifndef STOPBUTTON_H
#define STOPBUTTON_H

#include <QWidget>

class StopButton : public QWidget
{
    Q_OBJECT
public:
    explicit StopButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseReleaseEvent(QMouseEvent *event)override;

};

#endif // STOPBUTTON_H
