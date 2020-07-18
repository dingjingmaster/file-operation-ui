#ifndef FILEOPERATIONPROGRESSBAR_H
#define FILEOPERATIONPROGRESSBAR_H

#include <QWidget>

namespace Ui {
class FileOperationProgressBar;
}

class FileOperationProgressBar : public QWidget
{
    Q_OBJECT

public:
    explicit FileOperationProgressBar(QWidget *parent = nullptr);
    ~FileOperationProgressBar();

private:
    Ui::FileOperationProgressBar *ui;
};



#endif // FILEOPERATIONPROGRESSBAR_H
