#ifndef MAINPROGRESSBAR_H
#define MAINPROGRESSBAR_H

#include <QWidget>

class MainProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit MainProgressBar(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void paintFoot (QPainter& painter);
    void paintHeader (QPainter& painter);
    void paintContent (QPainter& painter);
    void paintProgress (QPainter& painter);

Q_SIGNALS:

private:
    // header
    QString m_title;
    int m_fix_width = 400;
    int m_fix_height = 160;
    int m_title_width = 320;
    int m_header_height = 30;

    // btn
    int m_btn_margin_top = 8;
    int m_btn_margin = 10;
    int m_btn_size = 16;

    // icon
    int m_icon_margin = 20;
    int m_icon_size = 64;

    // file name
    int m_file_name_height = 20;
    int m_file_name_margin = 10;

    // foot
    float m_foot_margin = 3;

    // progress
    float m_current_value = 0.8;
};

#endif // MAINPROGRESSBAR_H
