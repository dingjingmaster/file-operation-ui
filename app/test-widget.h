#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include "close-button.h"
#include "progress-bar.h"
#include "stop-button.h"

#include <QWidget>

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    TestWidget(QWidget* parent = 0);

    ~TestWidget ();

    void initUI ();

private:
    ProgressBar* pb = nullptr;
    CloseButton* cb = nullptr;
    StopButton * sb = nullptr;

};

#endif // TESTWIDGET_H
