#ifndef FILEOPERATIONPROCESS_H
#define FILEOPERATIONPROCESS_H

#include <QMap>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

class CloseButton;
class ProgressBar;
class DetailButton;
class StartStopButton;
class FileOperationProcess;

class FileOperationProcessBar : public QWidget
{
    Q_OBJECT
public:
    enum Status{
        STOP,
        PREPARE,
        RUNNING,
        FINISHED,
        CANCELED,
    };
public:
    static FileOperationProcessBar &getInstance();

    FileOperationProcess& addFileOperation ();

protected:
    void openDetail(bool open);

private:
    explicit FileOperationProcessBar(QWidget *parent = nullptr);
    ~FileOperationProcessBar();

private:
    bool m_detail_open = false;

    float m_width = 420;
    float m_height = 100;
    float m_max_height = 300;
    QLabel* m_detail_label = nullptr;
    QVBoxLayout* m_main_layout = nullptr;
    DetailButton* m_show_detail = nullptr;
    QHBoxLayout* m_detail_layout = nullptr;
    QVBoxLayout* m_process_layout = nullptr;
    QMap<FileOperationProcess, Status>* m_process = nullptr;
};

class FileOperationProcess : public QWidget
{
    Q_OBJECT
public:
    explicit FileOperationProcess(QWidget *parent = nullptr);
    ~FileOperationProcess();

public Q_SLOTS:
    void showDetail (bool detail);

private:
    bool m_show_detail = false;
    CloseButton* m_close = nullptr;
    QLabel* m_process_name = nullptr;
    QLabel* m_process_file = nullptr;
    ProgressBar* m_progress = nullptr;
    QLabel* m_process_percent = nullptr;
    QVBoxLayout* m_vbox_layout = nullptr;
    QHBoxLayout* m_main_layout = nullptr;
    QLabel* m_process_left_item = nullptr;
    StartStopButton* m_start_stop = nullptr;
};

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
    QRectF m_area;
    double m_current_value;
};

class DetailButton : public QWidget
{
    Q_OBJECT
public:
    explicit DetailButton(QWidget *parent = nullptr);

    void setSize (float size);

Q_SIGNALS:
    void valueChanged (bool open);

public Q_SLOTS:

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event)override;

private:
    float m_size = 12;
    bool m_open = false;
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

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseReleaseEvent(QMouseEvent *event)override;

private:
    float m_size = 12;
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
