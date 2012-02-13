/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Feb 13 23:17:11 2012
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include <QtGui/QScrollArea>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QScrollArea *scrollAreaLeft;
    QWidget *leftContents;
    QProgressBar *progressBar;
    QLineEdit *searchLineEdit;
    QTreeWidget *searchWidget;
    QWebView *webView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(1064, 629);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setAutoFillBackground(false);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 851, 612));
        sizePolicy.setHeightForWidth(layoutWidget->sizePolicy().hasHeightForWidth());
        layoutWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollAreaLeft = new QScrollArea(layoutWidget);
        scrollAreaLeft->setObjectName(QString::fromUtf8("scrollAreaLeft"));
        sizePolicy.setHeightForWidth(scrollAreaLeft->sizePolicy().hasHeightForWidth());
        scrollAreaLeft->setSizePolicy(sizePolicy);
        scrollAreaLeft->setMinimumSize(QSize(230, 0));
        scrollAreaLeft->setMaximumSize(QSize(230, 16777215));
        scrollAreaLeft->setWidgetResizable(true);
        leftContents = new QWidget();
        leftContents->setObjectName(QString::fromUtf8("leftContents"));
        leftContents->setGeometry(QRect(0, 0, 228, 598));
        progressBar = new QProgressBar(leftContents);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(0, 570, 230, 23));
        progressBar->setMinimumSize(QSize(230, 0));
        progressBar->setMaximumSize(QSize(230, 16777215));
        progressBar->setValue(24);
        progressBar->setTextVisible(false);
        searchLineEdit = new QLineEdit(leftContents);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setGeometry(QRect(0, 0, 241, 31));
        searchWidget = new QTreeWidget(leftContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        searchWidget->setHeaderItem(__qtreewidgetitem);
        searchWidget->setObjectName(QString::fromUtf8("searchWidget"));
        searchWidget->setGeometry(QRect(0, 40, 241, 521));
        scrollAreaLeft->setWidget(leftContents);

        gridLayout->addWidget(scrollAreaLeft, 0, 0, 1, 1);

        webView = new QWebView(layoutWidget);
        webView->setObjectName(QString::fromUtf8("webView"));
        sizePolicy.setHeightForWidth(webView->sizePolicy().hasHeightForWidth());
        webView->setSizePolicy(sizePolicy);
        webView->setUrl(QUrl("http://www.google.fi/"));

        gridLayout->addWidget(webView, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Jyv\303\244skyl\303\244n Rauhanyhdistys 100v", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
