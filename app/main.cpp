#include "file-operation-progressbar.h"

#include <QApplication>

int main (int argc, char* argv[])
{
    QApplication a (argc, argv);
    FileOperationProgressBar* fb = new FileOperationProgressBar();
//    fb.addFileOperation();

    fb->show();

    return a.exec();
}
