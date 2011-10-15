#include <QPainter>
#include "buttonarea.h"
#include "timeline.h"

Buttonarea::Buttonarea(QWidget *parent) :
    QWidget(parent)
{
    updateYears(1995,2005);
}

void Buttonarea::updateYears(int a, int b)
{
    this->oldest = a;
    this->newest = b;
}

void Buttonarea::paintEvent(QPaintEvent *)
    {
    int year = 0;
    year = oldest;

    int newest2 = this->newest + 1;
    int height = 10000; // this->height();
    int width = this->width() -235; // otetaan pois leveydestä, että napit jäävät kokonaan näkyviin
    int x = 20;
    int y = 0;
    int longBar = 5000; //height;//15;
    int shortBar = height;//7;

    QPen pen(Qt::gray, 1, Qt::DotLine);
    //QPen pen(Qt::black, 2, Qt::SolidLine);
    QPainter painter(this);
    painter.setPen(pen);

    int gap = newest2 - oldest;
    int scale = 0;
    if (gap != 0) { scale = (width -40) / gap; }

    // Kaikki dokumentit ovat samalta vuodelta
    if (gap == 1)
    {
        painter.drawLine(x, y, x, y + longBar);
        painter.drawText(QPoint(x - 18,y + 30),QString::number(year));
        year++;
        scale = (width -40) / 12;

        for (int i=0;i<12;i++) {
            x = x + scale;
            painter.drawLine(x, y + 5, x, y + 5 + shortBar);

        }
        painter.drawLine(x, y, x, y + longBar);
        painter.drawText(QPoint(x - 18,y + 30),QString::number(year));
    }
    // Merkit joka vuodelle
    else if (scale > 50)
    {
        do
        {
            painter.drawLine(x, y, x, y + longBar);
            year++;
            // <=
            if (year <=  newest2)
            {
                x = x + scale/2;
                painter.drawLine(x, y + 5, x, y + 5 + shortBar);
                x = x + scale/2;
            }
            // <=
        } while (year <= newest2);
    }
    // Merkit joka toinen vuosi
    else if (scale > 30)
    {
        do
        {
            painter.drawLine(x, y, x, y + longBar);
            if (year +2 <= newest2) year = year + 2;
            else year++;
            if (year <= newest2)
            {
                x = x + scale;
                painter.drawLine(x, y + 5, x, y + 5 + shortBar);
                x = x + scale;
            }
        } while (year <= newest2);
    }
    // Merkit joka viides vuosi
    else if (scale > 20)
    {
        scale = (scale / 2 ) * 5;
        do
        {
            painter.drawLine(x, y, x, y + longBar);
            if (year +5 <= newest2) year = year + 5;
            else year = newest2;
            if (year <= newest2)
            {
                x = x + scale;
                painter.drawLine(x, y + 5, x, y + 5 + shortBar);
                x = x + scale;
            }
        } while (year < newest2);
    }
    // Merkit joka kymmenes vuosi
    else
    {
        scale = (scale / 2 ) * 10;
        do
        {
            painter.drawLine(x, y, x, y + longBar);
            if (year +10 <= newest2) year = year + 10;
            else year = newest2;
            if (year <= newest2)
            {
                x = x + scale;
                painter.drawLine(x, y + 5, x, y + 5 + shortBar);
                x = x + scale;
            }
        } while (year < newest2);
    }
}
