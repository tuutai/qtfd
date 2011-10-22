#include "timelineview.h"
#include "ui_timelineview.h"

TimeLineView::TimeLineView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeLineView)
{
    ui->setupUi(this);
}

TimeLineView::~TimeLineView()
{
    delete ui;
}
