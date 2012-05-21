/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon May 21 20:13:13 2012
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
#include <QtGui/QDateEdit>
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
    QDateEdit *dateEdit;
    QLabel *label_2;
    QWebView *webView;
    QLabel *infoLabel;
    QLabel *label;
    QCommandLinkButton *buttonNext;
    QCommandLinkButton *buttonPrevious;

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
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        QBrush brush2(QColor(127, 127, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush2);
        QBrush brush3(QColor(170, 170, 170, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        QBrush brush4(QColor(255, 255, 220, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        MainWindow->setPalette(palette);
        MainWindow->setAutoFillBackground(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setAutoFillBackground(false);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 70, 851, 551));
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
        leftContents->setGeometry(QRect(0, 0, 238, 537));
        progressBar = new QProgressBar(leftContents);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(0, 520, 230, 23));
        progressBar->setMinimumSize(QSize(230, 0));
        progressBar->setMaximumSize(QSize(230, 16777215));
        progressBar->setValue(24);
        progressBar->setTextVisible(false);
        searchLineEdit = new QLineEdit(leftContents);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setGeometry(QRect(0, 100, 171, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Segoe UI"));
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        searchLineEdit->setFont(font);
        searchWidget = new QTreeWidget(leftContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        searchWidget->setHeaderItem(__qtreewidgetitem);
        searchWidget->setObjectName(QString::fromUtf8("searchWidget"));
        searchWidget->setGeometry(QRect(0, 150, 241, 371));
        QFont font1;
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        searchWidget->setFont(font1);
        commandLinkButton = new QCommandLinkButton(leftContents);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(168, 100, 71, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Segoe UI"));
        font2.setBold(true);
        font2.setWeight(75);
        font2.setKerning(true);
        commandLinkButton->setFont(font2);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ikonit/html/images/01-arrow-east.png"), QSize(), QIcon::Normal, QIcon::Off);
        commandLinkButton->setIcon(icon);
        groupBox = new QGroupBox(leftContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(3, 2, 231, 91));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Segoe UI"));
        font3.setBold(true);
        font3.setWeight(75);
        groupBox->setFont(font3);
        checkBoxVideo = new QCheckBox(groupBox);
        checkBoxVideo->setObjectName(QString::fromUtf8("checkBoxVideo"));
        checkBoxVideo->setGeometry(QRect(126, 21, 101, 17));
        checkBoxVideo->setFont(font3);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ikonit/html/images/dark-blue-circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        checkBoxVideo->setIcon(icon1);
        checkBoxVideo->setChecked(true);
        checkBoxAani = new QCheckBox(groupBox);
        checkBoxAani->setObjectName(QString::fromUtf8("checkBoxAani"));
        checkBoxAani->setGeometry(QRect(126, 41, 141, 17));
        checkBoxAani->setFont(font3);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ikonit/html/images/gray-circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        checkBoxAani->setIcon(icon2);
        checkBoxAani->setChecked(true);
        checkBoxKuva = new QCheckBox(groupBox);
        checkBoxKuva->setObjectName(QString::fromUtf8("checkBoxKuva"));
        checkBoxKuva->setGeometry(QRect(9, 41, 101, 17));
        checkBoxKuva->setFont(font3);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ikonit/html/images/dark-green-circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        checkBoxKuva->setIcon(icon3);
        checkBoxKuva->setChecked(true);
        checkBoxArtikkeli = new QCheckBox(groupBox);
        checkBoxArtikkeli->setObjectName(QString::fromUtf8("checkBoxArtikkeli"));
        checkBoxArtikkeli->setGeometry(QRect(9, 21, 131, 17));
        checkBoxArtikkeli->setFont(font3);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ikonit/html/images/dull-red-circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        checkBoxArtikkeli->setIcon(icon4);
        checkBoxArtikkeli->setChecked(true);
        dateEdit = new QDateEdit(groupBox);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setGeometry(QRect(120, 60, 101, 22));
        dateEdit->setFont(font3);
        dateEdit->setCurrentSection(QDateTimeEdit::YearSection);
        dateEdit->setCalendarPopup(false);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 60, 61, 16));
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
        infoLabel->setGeometry(QRect(250, 6, 811, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(infoLabel->sizePolicy().hasHeightForWidth());
        infoLabel->setSizePolicy(sizePolicy1);
        infoLabel->setFont(font3);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 231, 51));
        label->setPixmap(QPixmap(QString::fromUtf8(":/ikonit/rauhanyh.png")));
        label->setScaledContents(true);
        buttonNext = new QCommandLinkButton(centralWidget);
        buttonNext->setObjectName(QString::fromUtf8("buttonNext"));
        buttonNext->setGeometry(QRect(430, 30, 171, 41));
        buttonNext->setFont(font2);
        buttonNext->setIcon(icon);
        buttonPrevious = new QCommandLinkButton(centralWidget);
        buttonPrevious->setObjectName(QString::fromUtf8("buttonPrevious"));
        buttonPrevious->setGeometry(QRect(250, 30, 151, 41));
        buttonPrevious->setFont(font2);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ikonit/html/images/05-arrow-west.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonPrevious->setIcon(icon5);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Jyv\303\244skyl\303\244n Rauhanyhdistys 100v", 0, QApplication::UnicodeUTF8));
        searchLineEdit->setText(QApplication::translate("MainWindow", "Kirjoita hakusana", 0, QApplication::UnicodeUTF8));
        commandLinkButton->setText(QApplication::translate("MainWindow", "HAE", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Rajaus", 0, QApplication::UnicodeUTF8));
        checkBoxVideo->setText(QApplication::translate("MainWindow", "Video", 0, QApplication::UnicodeUTF8));
        checkBoxAani->setText(QApplication::translate("MainWindow", "\303\204\303\244ni", 0, QApplication::UnicodeUTF8));
        checkBoxKuva->setText(QApplication::translate("MainWindow", "Kuva", 0, QApplication::UnicodeUTF8));
        checkBoxArtikkeli->setText(QApplication::translate("MainWindow", "Artikkeli", 0, QApplication::UnicodeUTF8));
        dateEdit->setDisplayFormat(QApplication::translate("MainWindow", "d.M.yyyy", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Alkaen", 0, QApplication::UnicodeUTF8));
        infoLabel->setText(QApplication::translate("MainWindow", "Kaikki dokumentit - n\303\244ytet\303\244\303\244n 0-25", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        buttonNext->setText(QApplication::translate("MainWindow", " Seuraavat 25", 0, QApplication::UnicodeUTF8));
        buttonPrevious->setText(QApplication::translate("MainWindow", " Edelliset 25", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
