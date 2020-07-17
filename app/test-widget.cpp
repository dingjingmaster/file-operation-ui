#include "test-widget.h"

TestWidget::TestWidget(QWidget *parent) : QWidget(parent)
{
    pb = new ProgressBar(this);
    cb = new CloseButton(this);
    sb = new StopButton(this);
    db = new DetailButton(this);

    pb->setArea(QSize(300, 60));
    pb->updateValue(0.98);
    cb->setGeometry(300, 300, 12, 12);
    sb->setGeometry(200, 300, 12, 12);
    db->setGeometry(100, 300, 100, 100);
    db->setSize(60);
}

TestWidget::~TestWidget() {}

void TestWidget::initUI()
{
//    pb->show();
}
