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

 #ifndef FLOWLAYOUT_H
 #define FLOWLAYOUT_H

 #include <QLayout>
 #include <QRect>
 #include <QWidgetItem>
 //#include "qdocumentbutton.h"
 class FlowLayout : public QLayout
 {
 public:
     FlowLayout(QWidget *parent, int margin = 0, int spacing = -1);
     FlowLayout(int spacing = -1);
     ~FlowLayout();

     void addItem(QLayoutItem *item);
     Qt::Orientations expandingDirections() const;
     bool hasHeightForWidth() const;
     int heightForWidth(int) const;
     int count() const;
     QLayoutItem *itemAt(int index) const;
     QSize minimumSize() const;
     void setGeometry(const QRect &rect);
     QSize sizeHint() const;
     QLayoutItem *takeAt(int index);
     void setLayotInformation(int begin, int end, int width);
     void addYearInfo(int year);
     QList <int> years;
     void resetYearInfo();

 private:
     int doLayout(const QRect &rect, bool testOnly) const;
     int beginYear;
     int endYear;
     int width;
     QList<QLayoutItem *> itemList;
 };

 #endif
