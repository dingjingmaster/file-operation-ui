#include "file-operation-progress-bar.h"

#include <QApplication>

int main (int argc, char* argv[])
{
    QApplication a (argc, argv);
    FileOperationProcessBar& fb = FileOperationProcessBar::getInstance();
    FileOperationProcess* prc = fb.addFileOperation();
    fb.showProcess(*prc);

//    fb.show();

    return a.exec();
}
