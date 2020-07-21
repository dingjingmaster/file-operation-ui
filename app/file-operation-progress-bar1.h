#ifndef FILEOPERATIONPROCESS_H
#define FILEOPERATIONPROCESS_H

#include <QMap>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QMainWindow>
#include <QMutex>
#include <QListWidget>

class CloseButton;
class ProgressBar;
class DetailButton;
class StartStopButton;
class FileOperationProcess;

class FileOperationProcessBar : public QWidget
{
    Q_OBJECT
public:
    enum Status
    {
        STOP,
        PREPARE,
        RUNNING,
        FINISHED,
        CANCELED,
        FREE,
    };
public:
    static FileOperationProcessBar &getInstance();

    FileOperationProcess* addFileOperation ();
    void showProcess(FileOperationProcess& proc);
    void removeFileOperation(FileOperationProcess** fileOperation);

private:
    explicit FileOperationProcessBar(QWidget *parent = nullptr);
    ~FileOperationProcessBar();

public Q_SLOTS:
    void detailInfo (bool open);

private:
    float m_width = 500;
    float m_height = 150;
    float m_margin = 20;
    float m_max_height = 300;
    const int m_max_progressbar = 1;                               // reserved one for undo or redo

    QFrame* m_spline = nullptr;
    QLabel* m_detail_label = nullptr;
    QWidget* m_detail_widget = nullptr;
    QScrollArea* m_scroll_area = nullptr;
    QVBoxLayout* m_main_layout = nullptr;
    DetailButton* m_show_detail = nullptr;
    QHBoxLayout* m_detail_layout = nullptr;

    QWidget* m_scroll_widget = nullptr;
    QMainWindow* m_process_widget = nullptr;
    QVBoxLayout* m_process_layout = nullptr;

    int m_inuse_process = 0;
    QMutex *m_process_locker = nullptr;                             // maybe not need
    QMap<FileOperationProcess*, Status>* m_process = nullptr;       // all of processbar, fixme
};

class FileOperationProcess : public QWidget
{
    friend FileOperationProcessBar;
    Q_OBJECT
public:
    explicit FileOperationProcess(float width, float heigth, QWidget *parent = nullptr);

private:
    ~FileOperationProcess();
    void initParam ();

public Q_SLOTS:

private:
    CloseButton* m_close = nullptr;
    QLabel* m_process_name = nullptr;
    QLabel* m_process_file = nullptr;
    ProgressBar* m_progress = nullptr;
    QLabel* m_process_percent = nullptr;
    QHBoxLayout* m_vbox_layout = nullptr;
    QVBoxLayout* m_main_layout = nullptr;
    QLabel* m_process_left_item = nullptr;
    StartStopButton* m_start_stop = nullptr;
};

class ProgressBar : public QWidget
{
    friend FileOperationProcess;
    Q_OBJECT
public:
    explicit ProgressBar(QWidget *parent = nullptr);
    ~ProgressBar();

protected:
    void paintEvent(QPaintEvent *event) override;

public Q_SLOTS:
    void updateValue(double value);

public:

private:
    QRectF m_area;
    bool m_detail = false;
    double m_current_value = 1.0;
};

class DetailButton : public QWidget
{
    Q_OBJECT
public:
    explicit DetailButton(QWidget *parent = nullptr);

Q_SIGNALS:
    void valueChanged (bool open);

public Q_SLOTS:

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event)override;

private:
    float m_size = 18;
    bool m_open = true;
};

/**
 * @brief
 *
 */
class StartStopButton : public QWidget
{
    Q_OBJECT
public:
    explicit StartStopButton(QWidget *parent = nullptr);

Q_SIGNALS:
    void startStopClicked (bool start);
protected:
    void paintEvent(QPaintEvent *) override;
    void mouseReleaseEvent(QMouseEvent *event)override;

private:
    float m_size = 12;
    bool m_start = true;
};

class CloseButton : public QWidget
{
    Q_OBJECT
public:
    explicit CloseButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseReleaseEvent(QMouseEvent *event)override;

Q_SIGNALS:

private:
    float m_size = 12;
};

#endif // FILEOPERATIONPROCESS_H
