#include "file-operation-progressbar.h"
#include "ui_file-operation-progressbar.h"

FileOperationProgressBar::FileOperationProgressBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileOperationProgressBar)
{
    ui->setupUi(this);
}

FileOperationProgressBar::~FileOperationProgressBar()
{
    delete ui;
}
