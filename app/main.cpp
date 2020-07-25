#include "file-operation-progressbar.h"
#include "file-operation-error-handler.h"

#include <QDebug>
#include <QApplication>

int main (int argc, char* argv[])
{
    QApplication a (argc, argv);

//    FileOperationProgressBar* fb = FileOperationProgressBar::getInstance();

//    ProgressBar* pb = fb->addFileOperation();
//    pb->setFileName("111");

//    pb = fb->addFileOperation();
//    pb->setFileName("222");

////    pb = fb->addFileOperation();
////    pb->setFileName("333");

////    pb = fb->addFileOperation();
////    pb->setFileName("444");

////    pb = fb->addFileOperation();
////    pb->setFileName("555");

////    pb = fb->addFileOperation();
////    pb->setFileName("666");

////    pb = fb->addFileOperation();
////    pb->setFileName("777");

//    fb->show();

    // file error dialog
    FileOperationErrorHandler* h = new FileConflictDialog;

    GError* err = nullptr;

    h->handleError("aa", "bb", err, false);

    qDebug () << "bbb";


    return a.exec();
}
