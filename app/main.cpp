#include "progress-bar.h"
#include "test-widget.h"
#include <QWidget>
#include <QApplication>

int main (int argc, char* argv[])
{
    QApplication a (argc, argv);
    TestWidget* ts = new TestWidget(nullptr);
    ts->resize(500, 500);

    ts->show();

    return a.exec();
}
