#ifndef OTHERBUTTON_H
#define OTHERBUTTON_H

#include <QWidget>

class OtherButton : public QWidget
{
    Q_OBJECT
public:
    explicit OtherButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

Q_SIGNALS:

private:
    // button height
    int m_icon_margin = 6;
    int m_icon_size = 10;
    int m_button_heigth = 20;

    // text width
    int m_text_length = 100;
    QString m_text = "";
};

#endif // OTHERBUTTON_H
