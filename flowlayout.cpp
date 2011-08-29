/****************************************************************************
**
** Copyright (C) 2004-2008 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
**
** This file is part of the documentation of the Qt Toolkit.
**
** Licensees holding a valid Qt License Agreement may use this file in
** accordance with the rights, responsibilities and obligations
** contained therein.  Please consult your licensing agreement or
** contact qt-sales@nokia.com if any conditions of this licensing
** agreement are not clear to you.
**
** Further information about Qt licensing is available at:
** http://trolltech.com/products/appdev/licensing.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QtGui>

#include "flowlayout.h"

FlowLayout::FlowLayout(QWidget *parent, int margin, int spacing)
    : QLayout(parent)
{
    setMargin(margin);
    setSpacing(spacing);
}

FlowLayout::FlowLayout(int spacing)
{
    setSpacing(spacing);
}

FlowLayout::~FlowLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}



void FlowLayout::addItem(QLayoutItem *item)
{
    itemList.append(item);
}

int FlowLayout::count() const
{
    return itemList.size();
}

QLayoutItem *FlowLayout::itemAt(int index) const
{
    return (QLayoutItem *)itemList.value(index);
}

QLayoutItem *FlowLayout::takeAt(int index)
{
    if (index >= 0 && index < itemList.size())
        return (QLayoutItem *)itemList.takeAt(index);
    else
        return 0;
}

Qt::Orientations FlowLayout::expandingDirections() const
{
    return 0;
}

bool FlowLayout::hasHeightForWidth() const
{
    return true;
}

int FlowLayout::heightForWidth(int width) const
{
    int height = doLayout(QRect(0, 0, width, 0), true);
    return height;
}

void FlowLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

QSize FlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize FlowLayout::minimumSize() const
{
    QSize size;
    QLayoutItem *item;
    foreach (item, itemList)
        size = size.expandedTo(item->minimumSize());

    size += QSize(2*margin(), 2*margin());
    return size;
}

void FlowLayout::addYearInfo(int year)
{
    years.append(year);
}

void FlowLayout::resetYearInfo()
{
    years.clear();
}


void FlowLayout::setLayotInformation(int begin, int end, int width)
{
    this->beginYear = begin;
    this->endYear = end;
    //this->endYear = (int)(begin + (end-begin))
    this->width = width;
}

int FlowLayout::doLayout(const QRect &rect, bool testOnly) const
{

    //qDebug()<<endl;
    //qDebug()<<endl;
    //qDebug()<<"doLayout";

    //int x = rect.x();
    int y = rect.y();
    int lineHeight = 0;

    QLayoutItem *item;
    int lastYear = beginYear;
    //foreach (item, itemList) {
    for(int i = 0; i < itemList.count(); i++)
    {
        item = itemList.at(i);
        int year = years.at(i);
        //
        int xPosition  ;
        if(endYear-beginYear == 0)
            xPosition = 0;
        else
            //          "vuoden" pituus px   koko pit     / vuotta
            xPosition = (year - beginYear) * ((this->width - 60) / (endYear - beginYear));

        xPosition+=20;

        //qDebug()<<"this->width:"<<this->width;
        //qDebug()<<"(year - beginYear):"<<(year - beginYear);
        //qDebug()<<"xPosition:"<<xPosition;
        //qDebug()<<"(endYear + 1 - beginYear):"<<(endYear + 1 - beginYear);

        //if(lastYear == year)
            y = y + lineHeight;
        //else
        //    y = 0;

        //int nextX = x + item->sizeHint().width() + spacing();
        //if (nextX - spacing() > rect.right() && lineHeight > 0) {
        //    x = rect.x();
        //    y = y + lineHeight + spacing();
        //    nextX = x + item->sizeHint().width() + spacing();
        //    lineHeight = 0;
        //}

        if (!testOnly)
            item->setGeometry(QRect(QPoint(xPosition, y), item->sizeHint()));
            //item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

        //x = nextX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
        lastYear = year;
    }
    return y + lineHeight - rect.y();
}
