#ifndef FILEOPERATIONERRORHANDLER_H
#define FILEOPERATIONERRORHANDLER_H

#include <gio/gio.h>

#include <QCheckBox>
#include <QDialog>
#include <QLabel>

class FileOperationErrorHandler : public QDialog
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
        ExceptionType   error_type;
        int             error_code;
        QString         response_string;            // maybe i can use QMap to store result information
    } ResponseInfo;

    FileOperationErrorHandler(QDialog *parent = nullptr);
    virtual ~FileOperationErrorHandler();
    virtual ResponseInfo* handleError(const QString &srcUri, const QString &destDirUri,
                                     const GError *err, bool isCritical = false);
protected:
    bool getCritical ();
    QString getSrcUri ();
    QString getDestUri ();
    QString getErrorString ();

    void setSrcUri (QString uri);
    void setDestUri (QString uri);
    void setCritical (bool critical);
    void setErrorString (QString str);

protected:
    virtual ResponseInfo* packResult (int ret) = 0;

protected:
    bool m_is_critical;
    QString m_src_uri;
    QString m_dest_uri;
    QString m_error_string;
};

class FileConflictDialog : public FileOperationErrorHandler
{
    Q_OBJECT
public:
    FileConflictDialog(QDialog* parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void paintHeader (QPainter& painter);
    void paintContent (QPainter& painter);
//    void paintContent (QPainter& painter);
    virtual ResponseInfo* packResult (int ret) override;

private:
    float m_fix_width = 580;
    float m_fix_height = 498;
    float m_margin = 9;
    float m_margin_lr = 26;

    // header
    float m_title_margin_left = 44;
    float m_btn_size = 18;
    float m_title_width = 320;
    float m_header_height = 30;
    QString m_title_text = tr("File operation error");

    // text
    float m_text_margin_left = 26;
    float m_text_margin_top = 65;
    float m_text_height = 44;

    // content chose 1
    float m_ct1_margin_top = 119;
    float m_ct1_heigth = 116;
    float m_ct2_margin_top = 247;
    float m_ct2_heigth = 116;

    // check button
    float m_ck_margin_top = 385;
    float m_ck_height = 16;
};

#endif // FILEOPERATIONERRORHANDLER_H
