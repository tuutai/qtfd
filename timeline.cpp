#include <QPainter>
#include "xmlread.h"
#include "timeline.h"
#include "mainwindow.h"

Timeline::Timeline(QWidget *parent) :
    QWidget(parent)
{
    updateYears(1995,2005);
}

void Timeline::updateYears(int a, int b)
{
    this->oldest = a;
    this->newest = b;

    //this->newest = (int)(a + (b-a) * 1.2);
}


void Timeline::paintEvent(QPaintEvent *)
    {
        int year = 0;
        year = oldest;

        int newest2 = this->newest + 1;
        int height = this->height();
        int width = this->width();
        int x = 20;
        int y = height - 37;
        int longBar = 15;
        int shortBar = 7;

        //QPen pen(Qt::gray, 2, Qt::SolidLine);
        QPen pen(Qt::black, 2, Qt::SolidLine);
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
            QString months[12] = {"Tammi","Helmi","Maalis","Huhti","Touko","Kes" + QString::fromUtf8("ä"),"Hein" + QString::fromUtf8("ä"),"Elo","Syys","Loka","Marras","Joulu"};

            for (int i=0;i<12;i++) {
                x = x + scale;
                painter.drawLine(x, y + 5, x, y + 5 + shortBar);
                // keskitetään teksti oikein janan viivojen väliin
                painter.drawText(QPoint(x - (scale/2) -(months[i].length()*4),y + 30),months[i]);
            }
            painter.drawLine(x, y, x, y + longBar);
            painter.drawText(QPoint(x - 18,y + 30),QString::number(year));
        }
        // Kirjoitetaan vuosiluvut joka vuodelle
        else if (scale > 50)
        {
            do
            {
                painter.drawLine(x, y, x, y + longBar);
                painter.drawText(QPoint(x - 18,y + 30),QString::number(year));
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
        // Kirjoitetaan vuosiluvut joka toinen vuosi
        else if (scale > 30)
        {
            do
            {
                painter.drawLine(x, y, x, y + longBar);
                painter.drawText(QPoint(x - 18,y + 30),QString::number(year));
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
        // Kirjoitetaan vuosiluvut joka viides vuosi
        else if (scale > 20)
        {
            scale = (scale / 2 ) * 5;
            do
            {
                painter.drawLine(x, y, x, y + longBar);
                painter.drawText(QPoint(x - 18,y + 30),QString::number(year));
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
        // Kirjoitetaan vuosiluvut joka kymmenes vuosi
        else
        {
            scale = (scale / 2 ) * 10;
            do
            {
                painter.drawLine(x, y, x, y + longBar);
                painter.drawText(QPoint(x - 18,y + 30),QString::number(year));
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
