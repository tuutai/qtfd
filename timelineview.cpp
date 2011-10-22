#include <QDir>
#include <QDebug>
#include "timelineview.h"
#include "ui_timelineview.h"

TimeLineView::TimeLineView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeLineView)
{
    ui->setupUi(this);

    QString f = QDir::toNativeSeparators("html/timelineview.html");
    //qDebug() << f;
    this->ui->webView->load(QUrl(f));
}

TimeLineView::~TimeLineView()
{
    delete ui;
}

void TimeLineView::timeline_reload()
{
    this->ui->webView->reload();
}

