#ifndef DETAILBUTTON_H
#define DETAILBUTTON_H

#include <QWidget>

class DetailButton : public QWidget
{
    Q_OBJECT
public:
    explicit DetailButton(QWidget *parent = nullptr);

    void setSize (float size);

public Q_SLOTS:

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event)override;

private:
    float mSize = 12;
    bool mOpen = false;
};

#endif // DETAILBUTTON_H
