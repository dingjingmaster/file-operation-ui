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
    static FileOperationProgressBar* getInstance();

    ProgressBar* addFileOperation();
    void showProgress (ProgressBar& progress);
    void removeFileOperation(ProgressBar* progress);

private:
    explicit FileOperationProgressBar(QWidget *parent = nullptr);
    void showMore ();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void showWidgetList(bool show);

Q_SIGNALS:
    void cancelAll();

public Q_SLOTS:
    void mainProgressChange(QListWidgetItem *item);

private:
    // layout
    QVBoxLayout* m_main_layout = nullptr;

    // widget
    MainProgressBar* m_main_progressbar = nullptr;
    OtherButton* m_other_progressbar = nullptr;
    QListWidget* m_list_widget = nullptr;

    ProgressBar* m_current_main = nullptr;
    QMap<ProgressBar*, QListWidgetItem*>* m_progress_list = nullptr;
    QMap<QListWidgetItem*, ProgressBar*>* m_widget_list = nullptr;

    int m_show_items = 3;
    bool m_show_more = false;
    int m_progress_item_height = 40;
    int m_progress_list_heigth = 200;

    // ui
    int m_progress_size = 0;
    bool m_is_press = false;
    QPoint m_position;
};

class ProgressBar : public QWidget
{
    friend FileOperationProgressBar;
    Q_OBJECT
public:
    explicit ProgressBar (QWidget* parent = nullptr);
    void setFileName (QString fileName);
    void setIcon (QIcon icon);
    QString getFileName();
    QIcon getIcon();

private:
    ~ProgressBar();
    void initParam ();

Q_SIGNALS:
    void cancelled();
    void sendValue(double);
    void finished(ProgressBar* fop);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public Q_SLOTS:
    void updateValue(double);

private:
    int m_min_width = 400;
    int m_fix_height = 40;

    int m_btn_size = 16;
    int m_margin_ud = 2;
    int m_margin_lr = 8;
    int m_icon_size = 24;
    int m_text_height = 20;

    int m_progress_width = 80;
    int m_progress_height = 5;

    int m_percent_width = 20;

    // value
    double m_current_value = 0.8;
    QString m_file_name;
    QIcon m_icon;
};

class MainProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit MainProgressBar(QWidget *parent = nullptr);
    void setFileIcon (QIcon icon);
    void setFileName (QString name);
    void setTitle (QString title);

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
    QIcon m_icon;
    QString m_file_name;
    float m_move_x = 0.5;
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
