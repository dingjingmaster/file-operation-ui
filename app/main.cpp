#include "file-operation-progressbar.h"

#include <QListWidget>
#include <QPushButton>
#include <QApplication>

int main (int argc, char* argv[])
{
    QApplication a (argc, argv);
//    FileOperationProcessBar& fb = FileOperationProcessBar::getInstance();
//    FileOperationProcess* prc = fb.addFileOperation();
//    fb.showProcess(*prc);
//    fb.show();

//    QWidget* w = new QWidget;
//    QListWidget* l = new QListWidget(w);

//    w->setStyleSheet("QListWidget::Item:hover,QListWidget::Item:selected{background-color:rgba(22,29,36,0);}");

//    for (int i = 0; i < 15; ++i) {
//        QListWidgetItem* it = new QListWidgetItem;
//        QWidget* pb = new DetailButton;

//        l->addItem(it);
//        l->setItemWidget(it, pb);

//        l->removeItemWidget(it);
//        delete pb;
//        delete it;

//    }
//    l->setFocusPolicy(Qt::NoFocus);

//    l->setViewMode(QListView::ListMode);

//    w->setWid

//    w->show();



    // main
//    MainProgressBar* mp = new MainProgressBar;

//    mp->show();
    // other button
//    OtherButton* ob = new OtherButton;
//    ob->show();

    // progress list
//    ProgressList* pl = new ProgressList;
//    pl->show();

    FileOperationProgressBar* fb = FileOperationProgressBar::getInstance();

    ProgressBar* pb = fb->addFileOperation();
    pb->setFileName("111");

    pb = fb->addFileOperation();
    pb->setFileName("222");

    pb = fb->addFileOperation();
    pb->setFileName("333");

    pb = fb->addFileOperation();
    pb->setFileName("444");

    pb = fb->addFileOperation();
    pb->setFileName("555");

    pb = fb->addFileOperation();
    pb->setFileName("666");

    pb = fb->addFileOperation();
    pb->setFileName("777");

    fb->show();

    return a.exec();
}
