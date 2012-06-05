#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QPushButton>
#include <QLineEdit>
#include <QTreeWidget>
#include <QWebView>
#include "files.h"
#include "xmlread.h"
#include "search.h"
#include "flowlayout.h"
#include "categories.h"
#include "timeline.h"
#include "buttonarea.h"

class GSuggestCompletion;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadAndShowData(QList <int> indexes);
    QList<QPushButton *> buttonlist;
    XMLRead *xmlRead;
    Search *search;
    QList <int> years;
public slots:
    bool openfile(const QString filename);
    bool openUrl(const QUrl url);

protected:
    void resizeEvent ( QResizeEvent * e);
private:
    bool tempFlag;
    bool clearoffset;
    void timeLine();
    void createTags();
    QSignalMapper* signalMapper;
    Ui::MainWindow *ui;
    Timeline *widget;
    //QTreeWidget *searchWidget; // Sisaltaa vasemman reunan kategorianapit
    //int window_width;
    //int window_height;
    QLineEdit *searchbar;
    FlowLayout *flowLayout;
    void addCategoryButtons();
    Categories *cats;
    Buttonarea *backgroundwidget;
    void update_data(QList<Files *> _files);
    //QWebView *webView;
    GSuggestCompletion *completer;
    SearchCriteria GetSearchCriteria();
    QString GetCriteriaText();
    int dataCount;
    int offset;
    void refreshInfoLabel(bool comingFromSearchButton);

private slots:
    void selectCategory(QTreeWidgetItem* item,int n);
    void webViewProgress(int progress);
    void doSearch();
    void on_commandLinkButton_clicked();
    void searchCursorPositionChanged(int i,int i2);
    void on_searchLineEdit_lostFocus();
    void on_searchWidget_clicked(QModelIndex index);
    void on_pushButton_clicked();
    void on_checkBoxVideo_clicked();
    void on_checkBoxArtikkeli_clicked();
    void on_checkBoxKuva_clicked();
    void on_checkBoxAani_clicked();
    void on_buttonNext_clicked();
    void on_buttonPrevious_clicked();
    void on_dateEdit_dateChanged(QDate date);
};

#endif // MAINWINDOW_H
