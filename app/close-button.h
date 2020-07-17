#ifndef CLOSEBUTTON_H
#define CLOSEBUTTON_H

#include <QPushButton>

class CloseButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CloseButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseReleaseEvent(QMouseEvent *event)override;

Q_SIGNALS:

private:
    float mSize;
};

#endif // CLOSEBUTTON_H
