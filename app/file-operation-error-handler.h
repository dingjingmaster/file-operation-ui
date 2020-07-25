#ifndef FILEOPERATIONERRORHANDLER_H
#define FILEOPERATIONERRORHANDLER_H

#include <gio/gio.h>

#include <QCheckBox>
#include <QDialog>
#include <QLabel>
#include <QMap>

class BaseWidget;
class FileInformationLabel;

class BaseWidget : public QDialog
{
    Q_OBJECT
public:
    explicit BaseWidget (QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;

private:
    QString         m_title;
    float           m_btn_size = 20;
    float           m_margin_tp = 9;
    float           m_margin_lr = 16;
    float           m_btn_margin = 5;
    float           m_header_height = 30;

};

class FileOperationErrorHandler : public BaseWidget
{
    Q_OBJECT
    Q_PROPERTY(QString m_src_uri READ getSrcUri WRITE setSrcUri NOTIFY update)
    Q_PROPERTY(QString m_dest_uri READ getDestUri WRITE setDestUri NOTIFY update)
    Q_PROPERTY(QString m_error_string READ getErrorString WRITE setErrorString NOTIFY update)
    Q_PROPERTY(bool m_is_critical READ getCritical WRITE setCritical NOTIFY update)
public:
    enum ExceptionType
    {
        ET_GIO,
        ET_CUSTOM,
    };
    typedef struct _ResponseInfo
    {
        int                     error_code;
        bool                    do_similar;
        ExceptionType           error_type;
        QMap<QString, QString>  kv;
    } ResponseInfo;

    FileOperationErrorHandler(QDialog *parent = nullptr);
    virtual ~FileOperationErrorHandler();
    virtual ResponseInfo* handleError(const QString &srcUri, const QString &destDirUri,
                                     const GError *err, bool isCritical = false);
protected:
    bool getCritical ();
    bool getDoSimilar ();
    QString getSrcUri ();
    QString getDestUri ();
    QString getErrorString ();

    void setDoSimilar (bool sim);
    void setSrcUri (QString uri);
    void setDestUri (QString uri);
    void setCritical (bool critical);
    void setErrorString (QString str);

protected:
    virtual ResponseInfo* packResult (int ret) = 0;

protected:
    float m_margin_tp = 9;
    float m_margin_lr = 16;
    float m_header_height = 30;
    float m_btn_margin = 5;

    float m_btn_size = 20;

    QString m_title;

    bool m_do_similar;
    bool m_is_critical;
    QString m_src_uri;
    QString m_dest_uri;
    QString m_error_string;
};

class FileConflictDialog : public FileOperationErrorHandler
{
    Q_OBJECT
public:
    explicit FileConflictDialog(QDialog* parent = nullptr);
    ~FileConflictDialog();

protected:
    virtual ResponseInfo* packResult (int ret) override;

private:
    float m_fix_width = 580;
    float m_fix_height = 498;
    float m_margin = 9;
    float m_margin_lr = 26;

    float m_tip_y = 55;
    float m_tip_height = 50;

    float m_file_info1_top = 119;
    float m_file_info2_top = 247;
    float m_file_info_height = 116;

    float m_ck_btn_top = 385;
    float m_ck_btn_heigth = 18;

    float m_btn_top = 442;
    float m_btn_width = 120;
    float m_btn_heigth = 36;
    float m_btn_cancel_margin_left = 298;
    float m_btn_ok_margin_left = 434;

    QLabel* m_title = nullptr;
    QPushButton* m_mini = nullptr;
    QPushButton* m_close = nullptr;

    QLabel* m_tip = nullptr;
    FileInformationLabel* m_file_label1 = nullptr;
    FileInformationLabel* m_file_label2 = nullptr;

    QCheckBox* m_ck_box = nullptr;

    QPushButton* m_ok = nullptr;
    QPushButton* m_rename = nullptr;
    QPushButton* m_cancel = nullptr;
};

class FileInformationLabel : public QWidget
{
    Q_OBJECT

public:
    explicit FileInformationLabel(QWidget* parent = nullptr);

private:
    float m_fix_width = 528;
    float m_fix_heigth = 116;
    QIcon m_icon;
    QString m_op_name;
    QString m_file_name;
    QString m_file_size;
    QString m_modify_time;
    QString m_file_position;
};

class RenameDialog : public BaseWidget
{
    Q_OBJECT
public:
    explicit RenameDialog(QWidget* parent = nullptr);
    ~RenameDialog();

private:
    float m_fix_width = 550;
    float m_fix_height = 188;

    float m_margin = 9;
    float m_margin_lr = 26;

    QString m_title = tr("rename");
};

#endif // FILEOPERATIONERRORHANDLER_H
