#include "file-operation-process-bar.h"

#include <QApplication>

int main (int argc, char* argv[])
{
    QApplication a (argc, argv);
    FileOperationProcessBar& fb = FileOperationProcessBar::getInstance();
    fb.addFileOperation();

    fb.show();

    return a.exec();
}
