/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Apr 2 22:35:32 2012
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
#include <QtGui/QCheckBox>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
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
    QCommandLinkButton *commandLinkButton;
    QGroupBox *groupBox;
    QCheckBox *checkBoxVideo;
    QCheckBox *checkBoxAani;
    QCheckBox *checkBoxKuva;
    QCheckBox *checkBoxArtikkeli;
    QWebView *webView;
    QLabel *infoLabel;

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
        layoutWidget->setGeometry(QRect(0, 30, 851, 591));
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
        scrollAreaLeft->setMinimumSize(QSize(240, 0));
        scrollAreaLeft->setMaximumSize(QSize(240, 16777215));
        scrollAreaLeft->setWidgetResizable(true);
        leftContents = new QWidget();
        leftContents->setObjectName(QString::fromUtf8("leftContents"));
        leftContents->setGeometry(QRect(0, 0, 238, 577));
        progressBar = new QProgressBar(leftContents);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(0, 520, 230, 23));
        progressBar->setMinimumSize(QSize(230, 0));
        progressBar->setMaximumSize(QSize(230, 16777215));
        progressBar->setValue(24);
        progressBar->setTextVisible(false);
        searchLineEdit = new QLineEdit(leftContents);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setGeometry(QRect(0, 0, 171, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Segoe UI"));
        font.setBold(true);
        font.setWeight(75);
        searchLineEdit->setFont(font);
        searchWidget = new QTreeWidget(leftContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        searchWidget->setHeaderItem(__qtreewidgetitem);
        searchWidget->setObjectName(QString::fromUtf8("searchWidget"));
        searchWidget->setGeometry(QRect(0, 130, 241, 391));
        commandLinkButton = new QCommandLinkButton(leftContents);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(170, 0, 71, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Segoe UI"));
        font1.setBold(true);
        font1.setWeight(75);
        font1.setKerning(true);
        commandLinkButton->setFont(font1);
        groupBox = new QGroupBox(leftContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 50, 231, 71));
        groupBox->setFont(font);
        checkBoxVideo = new QCheckBox(groupBox);
        checkBoxVideo->setObjectName(QString::fromUtf8("checkBoxVideo"));
        checkBoxVideo->setGeometry(QRect(10, 20, 101, 17));
        checkBoxVideo->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ikonit/html/images/dark-blue-circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        checkBoxVideo->setIcon(icon);
        checkBoxVideo->setChecked(true);
        checkBoxAani = new QCheckBox(groupBox);
        checkBoxAani->setObjectName(QString::fromUtf8("checkBoxAani"));
        checkBoxAani->setGeometry(QRect(120, 40, 141, 17));
        checkBoxAani->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ikonit/html/images/gray-circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        checkBoxAani->setIcon(icon1);
        checkBoxAani->setChecked(true);
        checkBoxKuva = new QCheckBox(groupBox);
        checkBoxKuva->setObjectName(QString::fromUtf8("checkBoxKuva"));
        checkBoxKuva->setGeometry(QRect(10, 40, 101, 17));
        checkBoxKuva->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ikonit/html/images/dark-green-circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        checkBoxKuva->setIcon(icon2);
        checkBoxKuva->setChecked(true);
        checkBoxArtikkeli = new QCheckBox(groupBox);
        checkBoxArtikkeli->setObjectName(QString::fromUtf8("checkBoxArtikkeli"));
        checkBoxArtikkeli->setGeometry(QRect(120, 20, 131, 17));
        checkBoxArtikkeli->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ikonit/html/images/dull-red-circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        checkBoxArtikkeli->setIcon(icon3);
        checkBoxArtikkeli->setChecked(true);
        scrollAreaLeft->setWidget(leftContents);

        gridLayout->addWidget(scrollAreaLeft, 0, 0, 1, 1);

        webView = new QWebView(layoutWidget);
        webView->setObjectName(QString::fromUtf8("webView"));
        sizePolicy.setHeightForWidth(webView->sizePolicy().hasHeightForWidth());
        webView->setSizePolicy(sizePolicy);
        webView->setUrl(QUrl("http://www.google.fi/"));

        gridLayout->addWidget(webView, 0, 1, 1, 1);

        infoLabel = new QLabel(centralWidget);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));
        infoLabel->setGeometry(QRect(250, 10, 601, 21));
        infoLabel->setFont(font);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Jyv\303\244skyl\303\244n Rauhanyhdistys 100v", 0, QApplication::UnicodeUTF8));
        searchLineEdit->setText(QApplication::translate("MainWindow", "Kirjoita hakusana", 0, QApplication::UnicodeUTF8));
        commandLinkButton->setText(QApplication::translate("MainWindow", "HAE", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Lis\303\244rajaukset", 0, QApplication::UnicodeUTF8));
        checkBoxVideo->setText(QApplication::translate("MainWindow", "Video", 0, QApplication::UnicodeUTF8));
        checkBoxAani->setText(QApplication::translate("MainWindow", "\303\204\303\244ni", 0, QApplication::UnicodeUTF8));
        checkBoxKuva->setText(QApplication::translate("MainWindow", "Kuva", 0, QApplication::UnicodeUTF8));
        checkBoxArtikkeli->setText(QApplication::translate("MainWindow", "Artikkeli", 0, QApplication::UnicodeUTF8));
        infoLabel->setText(QApplication::translate("MainWindow", "KAIKKI DOKUMENTIT - N\303\204YTET\303\204\303\204N 50 KERRALLAAN", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
