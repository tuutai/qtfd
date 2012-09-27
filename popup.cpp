#include "popup.h"
#include "ui_popup.h"
#include <QString>

popup::popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::popup)
{
    ui->setupUi(this);
}

void popup::setTopic(const QString *s)
{
    this->setWindowTitle(*s);
}

void popup::setImage(const QString *s)
{
    ui->image->setPixmap(QPixmap::fromImage(QImage::QImage(*s)).scaled(ui->image->size(),Qt::KeepAspectRatio));
    ui->image->resize(ui->image->pixmap()->size());
}

void popup::setDescription(const QString *s)
{
    ui->description->setText(*s);
}


popup::~popup()
{
    delete ui;
}
