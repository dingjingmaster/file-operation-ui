#include "file-operation-progress-bar.h"

#include <QApplication>
#include <QListWidget>
#include <QPushButton>

int main (int argc, char* argv[])
{
    QApplication a (argc, argv);
//    FileOperationProcessBar& fb = FileOperationProcessBar::getInstance();
//    FileOperationProcess* prc = fb.addFileOperation();
//    fb.showProcess(*prc);
//    fb.show();

    QWidget* w = new QWidget;
    QListWidget* l = new QListWidget(w);

    w->setStyleSheet("QListWidget::Item:hover,QListWidget::Item:selected{background-color:rgba(22,29,36,0);}");

    for (int i = 0; i < 5; ++i) {
        QListWidgetItem* it = new QListWidgetItem;
        QWidget* pb = new DetailButton;

        l->addItem(it);
        l->setItemWidget(it, pb);

    }
    l->setFocusPolicy(Qt::NoFocus);

    l->setViewMode(QListView::ListMode);

//    w->setWid

    w->show();

    return a.exec();
}
