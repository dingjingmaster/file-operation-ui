#ifndef FILEOPERATIONPROGRESSBAR_H
#define FILEOPERATIONPROGRESSBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>

class ProgressBar;
class OtherButton;
class MainProgressBar;

class FileOperationProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit FileOperationProgressBar(QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void showWidgetList(bool show);

Q_SIGNALS:
    void cancelAll();

private:
    // layout
    QVBoxLayout* m_main_layout = nullptr;

    // widget
    MainProgressBar* m_main_progressbar = nullptr;
    OtherButton* m_other_progressbar = nullptr;
    QListWidget* m_list_widget = nullptr;

    ProgressBar* m_current_main = nullptr;
    QMap<ProgressBar*, QListWidgetItem*>* m_progress_list = nullptr;

    int m_progress_list_heigth = 60;

    // ui
    bool m_is_press = false;
    QPoint m_position;
};

class ProgressBar : public QWidget
{
    friend FileOperationProgressBar;
    Q_OBJECT
public:
    explicit ProgressBar (QWidget* parent = nullptr);

private:
    ~ProgressBar();
    void initParam ();
Q_SIGNALS:
    void cancelled();
    void finished(ProgressBar* fop);

protected:
    void paintEvent(QPaintEvent *event) override;

public Q_SLOTS:

private:
    int m_min_width = 400;
    int m_fix_height = 20;

    int m_margin_ud = 2;
    int m_margin_lr = 8;
    int m_icon_size = 16;
    int m_text_height = 10;
    int m_btn_size = 10;
    int m_progress_width = 80;
};

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
    void minimized();
    void closeWindow();

public Q_SLOTS:
    void updateValue (double);

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

    // percent
    int m_percent_margin = 15;
    int m_percent_height = 20;

    // foot
    float m_foot_margin = 3;

    // progress
    float m_current_value = 0.8;
};

class OtherButton : public QWidget
{
    Q_OBJECT
public:
    explicit OtherButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

Q_SIGNALS:
    void clicked (bool show);

private:
    // button height
    int m_icon_margin = 6;
    int m_icon_size = 10;
    int m_button_heigth = 20;

    // text width
    int m_text_length = 100;
    QString m_text = "";

    // show
    bool m_show = false;
};


#endif // FILEOPERATIONPROGRESSBAR_H
