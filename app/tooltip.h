#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QWidget>

class ToolTip : public QWidget
{
    Q_OBJECT
public:
    explicit ToolTip(QWidget *parent = nullptr);

Q_SIGNALS:

};

#endif // TOOLTIP_H
