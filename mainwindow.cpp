#include <QLabel>
#include <QScrollArea>
#include <QDesktopServices>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xmlread.h"
#include "searchbox.h"
#include "timeline.h"
#include "buttonarea.h"
#include "googlesuggest.h"
#include "QTimer"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tempFlag(false),
    dataCount(0),
    offset(0),
    clearoffset(false)
{
    ui->setupUi(this);

    QString f = QDir::toNativeSeparators("html/timelineview.html");
    this->ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    this->ui->webView->load(QUrl(f));
    connect(this->ui->webView,SIGNAL(linkClicked (const QUrl &)),this,SLOT(openUrl(const QUrl &)));
    connect(this->ui->webView,SIGNAL(loadProgress(int)), this, SLOT(webViewProgress(int)));

    // Luetaan xml-tiedosto
    this->xmlRead = new XMLRead();
    this->search = new Search();
    this->cats = new Categories();
    this->signalMapper = new QSignalMapper();
    this->xmlRead->readXML("meta.xml");

    qSort(this->xmlRead->files.begin(), this->xmlRead->files.end(), Files::fileLessThan);
    createTags();
    QList <int> intlist;
    intlist.append(-1);
    loadAndShowData(intlist);

    this->ui->searchLineEdit->setCursorPosition(0);
    connect(this->ui->searchLineEdit,SIGNAL(cursorPositionChanged(int,int)), this, SLOT(searchCursorPositionChanged(int,int)));

    completer = new GSuggestCompletion(this->search, this->ui->searchLineEdit);

    connect(this->ui->searchLineEdit, SIGNAL(returnPressed()),this, SLOT(doSearch()));

    // Luodaan kategoriarakenne
    addCategoryButtons();
    this->ui->buttonPrevious->setEnabled(offset > 0);
    this->ui->buttonNext->setEnabled(dataCount > 50);
    refreshInfoLabel(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_data( QList<Files *> _files){
    qDebug()<<"update_data alku";
    this->setCursor(Qt::WaitCursor);
    QFile datafile(QDir::toNativeSeparators("html/data.js"));
    datafile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&datafile);
    // Tulostetaan header

    out << "var timeline_data = {\n'dateTimeFormat': 'iso8601',\n"
    //  "'wikiURL': \"http://simile.mit.edu/shelf/\",\n"
    //  "'wikiSection': \"Simile Cubism Timeline\",\n\n"
        "'events' : [\n";

    // Aikajanan jaksot = kirjan luvut
    out << "\t{'start': '1870',\n"
           "\t 'end': '1911',\n"
           "\t 'title': 'Lestadiolaisuuden tulo ja alkuvaiheet',\n"
           "\t 'description' : '',\n"
           "\t 'isInstant' : true,\n"
           "\t 'color': 'green'\n"
           "\t},\n"
           "\t{'start': '1911',\n"
           "\t 'end': '1945',\n"
           "\t 'title': 'Rauhanyhdistyksen perustaminen tuo j‰ntevyytt‰',\n"
           "\t 'description' : '',\n"
           "\t 'isInstant' : true,\n"
           "\t 'color': 'blue'\n"
           "\t},\n"
           "\t{'start': '1945',\n"
           "\t 'end': '1974',\n"
           "\t 'title': 'Aktiivista toimintaa ja j‰lleenrakennustyˆt‰',\n"
           "\t 'description' : '',\n"
           "\t 'isInstant' : true,\n"
           "\t 'color': 'gray'\n"
           "\t},\n"
           "\t{'start': '1974',\n"
           "\t 'end': '2011',\n"
           "\t 'title': 'Vilkas yhdistys Taulum‰ell‰',\n"
           "\t 'description' : '',\n"
           "\t 'isInstant' : true,\n"
           "\t 'color': 'red'\n"
           "\t},\n";

    // tulostetaan linkit
    //QList<Files *> _files = this->xmlRead->files;
    bool comma = false;
    QString alkuStr = "";
    QString loppuStr = "";

    if (this->clearoffset) this->offset = 0;
    this->clearoffset = true;

    //    int mod = indexes.count() / 50;
    //    if(mod == 0 )
    //        mod = 1;

    //    if (indexes.at(0) == -1)
    //        mod = _files.count() / 50;

    dataCount = _files.count();
    this->ui->buttonNext->setEnabled(offset + 50 < dataCount);
    int shownFiles = 0;
    for (int i = offset; i < _files.count(); i++)
    {
        if(i - offset > 50)
            break;
        Files *f = _files.at(i);

        if(alkuStr == "")
            alkuStr = f->date.toString("yyyy");
        loppuStr = f->date.addYears(5).toString("yyyy");

        if (comma) out << ",\n";
        QString path = "../files/";
        QString f_name = path.append(f->name);
        //qDebug() << f->date <<" --- " <<f->date.toString("yyyy-MM-dd");
        out << "\t{'start': '"<<f->date.toString("yyyy-MM-dd")<<"',\n"
               "\t'title': '"<<f->topic<<"',\n"
               "\t'description': '"<<f->description<<"',\n";
        if (f->name.endsWith(".jpg",Qt::CaseInsensitive)){
            out << "\t'image': '../thumbnails/thumb."<<f->name<<"',\n";
            out << "\t'icon': 'images/dark-green-circle.png',\n";
        }
        else if (f->name.endsWith(".mpg",Qt::CaseInsensitive)){
            out << "\t'image': 'images/video.png',\n";
            out << "\t'icon': 'images/dark-blue-circle.png',\n";
        }
        else if (f->name.endsWith(".pdf",Qt::CaseInsensitive)){
            out << "\t'image': 'images/pdf.png',\n";
            out << "\t'icon': 'images/dull-red-circle.png',\n";
        }
        else if (f->name.endsWith(".mp3",Qt::CaseInsensitive)){
            out << "\t'image': 'images/audio.png',\n";
            out << "\t'icon': 'images/gray-circle.png',\n";
        }

        /*
            out << "\t'image': '"<<f_name<<"',\n";
        //         "\t'image': 'http://images.allposters.com/images/AWI/NR096_b.jpg',\n"
        */
        out << "\t'link': '"<<f_name<<"'\n"
               "\t}";
        comma = true;
        shownFiles ++;

    }
    // tulostetaan footer
    out << "\n\n]\n}\n";
    out << "var TIMELINE_START = new Date(Date.UTC(" + alkuStr  + ", 0, 1));\n"
          + "var TIMELINE_STOP = new Date(Date.UTC(" + loppuStr + ", 0, 1));\n";

    datafile.close();
    this->ui->webView->reload();
    this->setCursor(Qt::ArrowCursor);
    qDebug()<<"update_data loppu";

    return;
}

void MainWindow::loadAndShowData(QList <int> indexes)
{
    SearchCriteria crit = this->GetSearchCriteria();
    QList<Files *> _files = this->xmlRead->files;
    QList<Files *> retFiles;
    for (int i = 0; i < _files.count(); i++)
    {
        Files *f = _files.at(i);
        if (f->name.endsWith(".jpg"))
        {
            if(!crit.showKuva)
                continue;
        }

        else if (f->name.endsWith(".mpg"))
        {
            if(!crit.showVideo)
                continue;
        }
        else if (f->name.endsWith(".pdf"))
        {
            if(!crit.showArtikkeli)
                continue;
        }
        else if (f->name.endsWith(".mp3"))
        {
            if(!crit.showAani)
                continue;
        }
        if (!indexes.contains(i) && !indexes.contains(-1)) continue;
        retFiles.append(_files.at(i));
    }
    this->update_data(retFiles);
}

void MainWindow::createTags()
{
    QString tag;
    QList<Files *> _files = this->xmlRead->files;
    for (int i = 0; i < _files.count(); i++)
    {
        Files *f = _files.at(i);
        for (int a=0;a<f->tags.length();a++)
        {
            tag = f->tags.at(a);
            this->search->addTag(tag, i);
        }
    }
}

bool MainWindow::openfile(const QString filename){
    QString path = QDir::toNativeSeparators("files/");
    QString f = path.append(filename); //.toLocal8Bit().constData();
    return QDesktopServices::openUrl(QUrl(f));
}

bool MainWindow::openUrl(const QUrl url){
    return QDesktopServices::openUrl(url);
}

void MainWindow::addCategoryButtons()
{
    QTreeWidgetItem *q, *qi;
    //searchWidget = new QTreeWidget(ui->centralWidget);
    q = this->ui->searchWidget->headerItem();
    q->setText(0,"Kategoriat");

    // Initialize category structure

    QList<Files *> _files = this->xmlRead->files;
    QString parentname, subcatname;
    for (int i = 0; i < _files.count(); i++)
    {
        Files *f = _files.at(i);
        for (int a=0;a<f->cat.length();a++)
        {
            Category ct = f->cat.at(a);
            parentname = ct.catname;
            //adding parent category
            this->cats->addCat(* new QString(),parentname,i);
            for (int b=0;b<ct.subcats.length();b++)
            {
                subcatname = ct.subcats.at(b);
                this->cats->addCat(parentname,subcatname,i);
            }
        }
    }

    // Go through categories and add the corresponding items to tree
    QList <QString> categorynames = this->cats->getCats();
    QList <QString> subcats;
    QString catname;
    for (int d=0;d<categorynames.length();d++)
    {
        catname = categorynames.at(d);
        qi = new QTreeWidgetItem(this->ui->searchWidget);
        qi->setText(0,catname);

        // make subcategory items
        subcats = this->cats->getSubCats(catname);
        for (int e=0;e<subcats.length();e++)
        {
            subcatname = subcats.at(e);
            q = new QTreeWidgetItem(qi);
            q->setText(0,subcatname);
        }
    }
    connect(this->ui->searchWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            SLOT(selectCategory(QTreeWidgetItem*,int)));
    //this->ui->searchWidget->show();
}

void MainWindow::selectCategory(QTreeWidgetItem* item,int n)
{
    QTreeWidgetItem* p = item->parent();
    QString parentname = "";
    QString catname = item->text(n);
    if (p) // parent found
        parentname = p->text(n);
    QList <int> list = this->cats->getIndexes(parentname,catname);
    this->loadAndShowData(list);
    tempFlag = true;
    this->ui->searchLineEdit->setText("Kirjoita hakusana");
    this->ui->searchLineEdit->setCursorPosition(0);
    tempFlag = false;

    refreshInfoLabel(false);
    return;
}

void MainWindow::webViewProgress(int progress)
{
    this->ui->progressBar->setValue(progress);

    //if(progress != 100)
    this->ui->progressBar->setVisible(progress != 100);

    //this->setWindowTitle(QString::number(progress));
}

void MainWindow::doSearch()
{
    //offset = 0;
    completer->preventSuggest();
    this->ui->searchWidget->clearSelection();
    // update buttons in the main view
    QList <int> indexes = this->search->getIndexes(this->ui->searchLineEdit->text());
    //MainWindow *m = reinterpret_cast<MainWindow*> (this->parent());
    //qDebug() << "doSearch";
    if (indexes.count() == 1)
    {
        this->loadAndShowData(indexes);
        //QString url = QString(GSEARCH_URL).arg(text());
        //QDesktopServices::openUrl(QUrl(url));
        //this->ui->infoLabel->setText("HAKUSANA: " + this->ui->searchLineEdit->text() + ", " + QString::number(this->dataCount) + " hakutulos"+ GetCriteriaText());
    }
    else if (indexes.count() > 1)
    {
        this->loadAndShowData(indexes);
        //this->ui->infoLabel->setText("HAKUSANA: " + this->ui->searchLineEdit->text() + ", " + QString::number(this->dataCount) + " hakutulosta (n‰ytet‰‰n "+QString::number(offset)+"-"+QString::number(offset+50) +")"+ GetCriteriaText() );
    }
    else
    {
        //this->ui->infoLabel->setText("HAKUSANA: " + this->ui->searchLineEdit->text() + ", ei yht‰‰n hakutulosta"+ GetCriteriaText());
    }
        refreshInfoLabel(true);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    if((qApp->mouseButtons() & Qt::LeftButton))
    {
        qDebug()<<"Tultiin resizeen hiiri alhaalla";

        return;
    }
    qDebug()<<"Tultiin resizeen";
    if( e->oldSize() == e->size())
        return;
    qDebug()<<"Tultiin resizeen - muuttui:"<<e->size().width()<<","<<e->size().height();
    this->ui->layoutWidget->resize(this->ui->centralWidget->size());
    qDebug()<<"Tultiin resizeen - pois";
}


void MainWindow::on_commandLinkButton_clicked()
{
    searchCursorPositionChanged(0,0);
    this->offset = 0;
    doSearch();
}

void MainWindow::searchCursorPositionChanged(int i, int i2)
{
    if(tempFlag)
        return;
    if(this->ui->searchLineEdit->text() == "Kirjoita hakusana")
        this->ui->searchLineEdit->setText("");
}

void MainWindow::on_searchLineEdit_lostFocus()
{
    if(this->ui->searchLineEdit->text() == "")
    {
        tempFlag = true;
        this->ui->searchLineEdit->setText("Kirjoita hakusana");
        this->ui->searchLineEdit->setCursorPosition(0);
        tempFlag = false;
    }
}

void MainWindow::on_searchWidget_clicked(QModelIndex index)
{
    this->offset = 0;
}

void MainWindow::on_pushButton_clicked()
{
    this->ui->checkBoxAani->setChecked(true);
    this->ui->checkBoxVideo->setChecked(true);
    this->ui->checkBoxArtikkeli->setChecked(true);
    this->ui->checkBoxKuva->setChecked(true);
    this->ui->checkBoxAani->setVisible(this->ui->searchWidget->y()<=100);
    this->ui->checkBoxVideo->setVisible(this->ui->searchWidget->y()<=100);
    this->ui->checkBoxArtikkeli->setVisible(this->ui->searchWidget->y()<=100);
    this->ui->checkBoxKuva->setVisible(this->ui->searchWidget->y()<=100);

    if(this->ui->searchWidget->y()<100)
    {
        //Show
        this->ui->searchWidget->setGeometry(this->ui->searchWidget->x(), 100, this->ui->searchWidget->width(), this->ui->searchWidget->height());
    }
    else
    {
        //Hide
        this->ui->searchWidget->setGeometry(this->ui->searchWidget->x(), 60, this->ui->searchWidget->width(), this->ui->searchWidget->height());
    }
    on_checkBoxVideo_clicked();
}

SearchCriteria MainWindow::GetSearchCriteria()
{
    SearchCriteria crit;
    crit.showAani = this->ui->checkBoxAani->isChecked();
    crit.showVideo = this->ui->checkBoxVideo->isChecked();
    crit.showKuva = this->ui->checkBoxKuva->isChecked();
    crit.showArtikkeli = this->ui->checkBoxArtikkeli->isChecked();
    return crit;
}

void MainWindow::on_checkBoxVideo_clicked()
{
    if(this->ui->searchLineEdit->text() != "" && this->ui->searchLineEdit->text() != "Kirjoita hakusana") {
        doSearch();
    }
    else if(this->ui->searchWidget->selectedItems().count() > 0)
        selectCategory(this->ui->searchWidget->selectedItems().first(),0 );
    else
    {
        QList <int> intlist;
        intlist.append(-1);
        loadAndShowData(intlist);
    }

    refreshInfoLabel(false);
}

void MainWindow::on_checkBoxArtikkeli_clicked()
{
    on_checkBoxVideo_clicked();
}

void MainWindow::on_checkBoxKuva_clicked()
{
    on_checkBoxVideo_clicked();
}

void MainWindow::on_checkBoxAani_clicked()
{
    on_checkBoxVideo_clicked();
}

QString MainWindow::GetCriteriaText()
{
    QString retVal = " (";
    bool comma = false;
    SearchCriteria crit = this->GetSearchCriteria();
    if(crit.showAani)
    {
        retVal = retVal + "ƒ‰ni";
        comma = true;
    }
    if(crit.showArtikkeli)
    {
        if(comma)
            retVal = retVal + ", ";
        retVal = retVal + "Artikkeli";
        comma = true;
    }
    if(crit.showKuva)
    {
        if(comma)
            retVal = retVal + ", ";
        retVal = retVal + "Kuva";
        comma = true;
    }
    if(crit.showVideo)
    {
        if(comma)
            retVal = retVal + ", ";
        retVal = retVal + "Video";
        comma = true;
    }
    retVal = retVal+")";

            if(!comma)
                return "";
return retVal;

}

void MainWindow::on_buttonNext_clicked()
{
    this->clearoffset = false;
    offset += 50;
    this->ui->buttonNext->setEnabled(offset + 50 < dataCount);
    this->ui->buttonPrevious->setEnabled(offset > 0);
    on_checkBoxVideo_clicked();

}

void MainWindow::on_buttonPrevious_clicked()
{
    this->clearoffset = false;
    if(offset > 0)
        offset -= 50;

    this->ui->buttonNext->setEnabled(offset + 50 < dataCount);
    this->ui->buttonPrevious->setEnabled(offset > 0);
    on_checkBoxVideo_clicked();
}

void MainWindow::refreshInfoLabel(bool comingFromSearchButton)
{
    if(comingFromSearchButton)
    {
        if(this->ui->searchLineEdit->text() != "" && this->ui->searchLineEdit->text() != "Kirjoita hakusana")
        {
            if (this->dataCount == 1)
                   this->ui->infoLabel->setText("HAKUSANA: " + this->ui->searchLineEdit->text() + ", " + QString::number(this->dataCount) + " hakutulos" + GetCriteriaText() );
               else if (this->dataCount <= 50)
                   this->ui->infoLabel->setText("HAKUSANA: " + this->ui->searchLineEdit->text() + ", " + QString::number(this->dataCount) + " hakutulosta " + GetCriteriaText() );
               else
                   this->ui->infoLabel->setText("HAKUSANA: " + this->ui->searchLineEdit->text() + ", " + QString::number(this->dataCount) + " hakutulosta (n‰ytet‰‰n "+QString::number(offset)+"-"+QString::number(offset+50) +")" + GetCriteriaText() );
        }
        else
        {
            this->ui->infoLabel->setText("Yhteens‰ " + QString::number(dataCount) + ", n‰ytet‰‰n "+ QString::number(offset) + "-" +QString::number(offset+50) +" "+ GetCriteriaText());
        }
    }
    else if(this->ui->searchWidget->selectedItems().count() > 0)
    {
        QTreeWidgetItem *t = this->ui->searchWidget->selectedItems().first();
        QString catname = t->text(0);

        if(this->dataCount == 1)
               this->ui->infoLabel->setText("KATEGORIA: " + catname + ", " + QString::number(this->dataCount) + " hakutulos"+ GetCriteriaText());
        else if (this->dataCount <= 50)
               this->ui->infoLabel->setText("KATEGORIA: " + catname + ", " + QString::number(this->dataCount) + " hakutulosta"+ GetCriteriaText());
        else
               this->ui->infoLabel->setText("KATEGORIA: " + catname + ", " + QString::number(this->dataCount) + " hakutulosta (n‰ytet‰‰n " + QString::number(offset) + "-" + QString::number(offset+50) + ")" + GetCriteriaText());
    }
    else
    {
        this->ui->infoLabel->setText("Yhteens‰ " + QString::number(dataCount) + ", n‰ytet‰‰n "+ QString::number(offset) + "-" +QString::number(offset+50) +" "+ GetCriteriaText());
    }
}
