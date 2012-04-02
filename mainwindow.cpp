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
    dataCount(0)
{

    ui->setupUi(this);



    //this->setWindowTitle("T‰ss‰ voidaan asettaa title");
    //this->window_width = 1100;
    //this->window_height = 500;
    //this->resize(1084, 560);

    // ScrollArea sis‰lt‰‰ kaikki napit/dokumentit
    //QScrollArea *scrollArea = ui->scrollArea;

    //scrollArea->setGeometry(QRect(240, 40, this->window_width-265, this->window_height-30));
    // Timeline sis‰lt‰‰ piirretyn aikajanan
    //this->webView = new QWebView(ui->scrollArea_2);
    //this->webView->setGeometry(QRect(0, -1, 801, 551));
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
    addButtons(intlist);

    this->ui->searchLineEdit->setCursorPosition(0);
    connect(this->ui->searchLineEdit,SIGNAL(cursorPositionChanged(int,int)), this, SLOT(searchCursorPositionChanged(int,int)));

    completer = new GSuggestCompletion(this->search, this->ui->searchLineEdit);

    connect(this->ui->searchLineEdit, SIGNAL(returnPressed()),this, SLOT(doSearch()));

    // Luodaan hakuboxi
    //SearchBox *searchEdit = new SearchBox(this->search, this);
    //this->ui->scrollAreaLeft->setWidget(s);
    //this->ui->scrollAreaWidgetContents = searchEdit;
    //searchEdit->setGeometry(QRect(10, 12, 240, 25));
    //searchEdit->show();

    // Luodaan kategoriarakenne
    addCategoryButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_data(QList <int> indexes, SearchCriteria crit){
    qDebug()<<"update_data alku";
    this->setCursor(Qt::WaitCursor);
    QFile datafile(QDir::toNativeSeparators("html/data.js"));
    datafile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&datafile);
    // Tulostetaan header

    out << "var timeline_data = {\n'dateTimeFormat': 'iso8601',\n"
//        "'wikiURL': \"http://simile.mit.edu/shelf/\",\n"
//        "'wikiSection': \"Simile Cubism Timeline\",\n\n"
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
    QList<Files *> _files = this->xmlRead->files;
    bool comma = false;
    QString alkuStr = "";
    QString loppuStr = "";

    int mod = indexes.count() / 50;
    if(mod == 0 )
        mod = 1;

    if (indexes.at(0) == -1)
        mod = _files.count() / 50;
    dataCount = 0;
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
        if(i != 0 && i%mod != 0) continue;

        if (!indexes.contains(i) && !indexes.contains(-1)) continue;
        //qDebug() << _files.at(i)->date;

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
        else if (f->name.endsWith(".mpg",Qt::CaseInsensitive)) out << "\t'icon': 'images/dark-blue-circle.png',\n";
        else if (f->name.endsWith(".pdf",Qt::CaseInsensitive)) out << "\t'icon': 'images/dull-red-circle.png',\n";
        else if (f->name.endsWith(".mp3",Qt::CaseInsensitive)) out << "\t'icon': 'images/gray-circle.png',\n";

/*
            out << "\t'image': '"<<f_name<<"',\n";
//               "\t'image': 'http://images.allposters.com/images/AWI/NR096_b.jpg',\n"
*/
        out << "\t'link': '"<<f_name<<"'\n"
               "\t}";
        comma = true;
        dataCount ++;

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


void MainWindow::addButtons(QList <int> indexes)
{
    this->update_data(indexes, this->GetSearchCriteria());
    return;


    QList<Files *> _files = this->xmlRead->files;
    //if (this->widget->layout()) delete this->widget->layout();
    //if (this->flowLayout->isEmpty())
    //{
    //        qDebug() << "layout is empty";
    //        delete this->flowLayout;
    //}

    buttonlist.clear();

    QLayoutItem *wItem;
    while ((wItem = this->backgroundwidget->layout()->takeAt(0)) != 0)
         delete wItem->widget();

    FlowLayout *f = reinterpret_cast<FlowLayout*>(this->backgroundwidget->layout());

    f->resetYearInfo();

    int x_offset = 0;
    int newest = 0;
    int oldest = 0;

    for (int i = 0; i < _files.count(); i++)
    {
        if (!indexes.contains(i) && !indexes.contains(-1)) continue;
        //qDebug() << _files.at(i)->date;
        Files *f = _files.at(i);
        QString iconpath = "";
        if (f->name.endsWith(".pdf")) iconpath = "images/File.png";
        else if (f->name.endsWith(".avi")) iconpath = "images/Blue.png";
        else iconpath = "images/Green.png";
        QIcon *icon = new QIcon(iconpath);
        QPushButton *p;
        if (icon->isNull())
            qDebug() << "icon is null";
        QString buttonText = "";
        if (f->topic.length()> 35)
        {
            buttonText = f->topic.left(32);
            buttonText.append("...");
        }
        else buttonText = f->topic;
        //qDebug()<<buttonText;
        p= new QPushButton(*icon, buttonText,this->backgroundwidget);
        //p = new QDocumentButton(*icon, buttonText,this->widget);
        //qDebug()<<p->width();
        bool ok;
        //p->documentYear =  f->year.toInt(&ok, 10);
        //p = new QPushButton(*icon, f->topic,this->widget);
        p->setObjectName(f->name);
        //qDebug() << f->name;
        p->setToolTip(f->date.toString("dd.MM.yyyy").append("\n").append(f->description));

        flowLayout->addWidget(p );
        flowLayout->addYearInfo(f->year.toInt(&ok, 10));
        //p->setGeometry(QRect(190+x_offset, 30, 40, 40));
        buttonlist.append(p);

        //this->signalMapper->setMapping(p, f->name);
        this->signalMapper->setMapping(p, i);
        QObject::connect(p, SIGNAL(clicked()), this->signalMapper, SLOT (map()));

        x_offset += 50;

        // Take first and last year for timeline
       if (oldest == 0 || f->year.toInt() < oldest) { oldest = f->year.toInt(); }
       if (newest == 0 || f->year.toInt() > newest) { newest = f->year.toInt(); }
    }

    //qDebug()<<"oldest % 5 = "<< oldest % 5;
    //qDebug()<<"oldest % 10 = "<< oldest % 10;

    // Aloitetaan aikajanan piirt‰minen ensimm‰ist‰ dokumenttia edelt‰v‰st‰ 0 tai 5 vuodesta
    if (oldest % 5 != 0) {
     oldest = oldest - (oldest % 5);
    } else if (oldest % 10 != 0) {
    oldest = oldest - (oldest % 10);
    }

    int width = this->widget->width()-235; // otetaan pois leveydest‰, ett‰ napit j‰‰v‰t kokonaan n‰kyviin

    //Piirret‰‰n v‰h‰n yli, ett‰ "tuoreimmat" napit mahtuvat n‰kyviin
    //Napit piirret‰‰n aina ko. vuodesta oikealle.

    //qDebug()<<"Aikajanan aito pituus"<<newest-oldest;
    //qDebug()<<"Aikajanan kasvatettu pituus"<<int((newest-oldest) * 1.2);
    //newest = oldest + int((newest-oldest) * 1.2);
    //qDebug()<<"Uusi newest"<<newest;

    flowLayout->setLayotInformation(oldest, newest, width);

    if (oldest != 0) { this->years.append(oldest); }
    if (newest != 0) { this->years.append(newest); }

    Timeline *t =   reinterpret_cast<Timeline*> (this->widget);
    t->updateYears(oldest, newest);

    Buttonarea *b =   reinterpret_cast<Buttonarea*> (this->backgroundwidget);
    b->updateYears(oldest, newest);

    this->widget->repaint();
    this->backgroundwidget->repaint();
    this->backgroundwidget->setLayout(flowLayout);
    flowLayout->update();
    //    QObject::connect(this->signalMapper, SIGNAL(mapped(const QString &)),
    //                     this, SLOT(openfile(const QString &)));
    QObject::connect(this->signalMapper, SIGNAL(mapped(const int &)),
                     this, SLOT(showFileData(const int &)));
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

bool MainWindow::showFileData(const int index){
//    // Here we show popup window that has file metadata information
//    QFrame* popup1 = new QFrame(this, Qt::Popup | Qt::Window );
//    popup1->resize(600,280);
//    popup1->setGeometry(QRect(this->window_width/2-300, this->window_height/2 -140,600,280));

//    Files *_f = this->xmlRead->files.at(index);

//    QLabel *topic = new QLabel(_f->topic, popup1);
//    topic->setGeometry(QRect(20,20,560,20));

//    // Collect all metadata to description text
//    QString *description = new QString();
//    description->append("Otsikko: "+_f->topic+"\n");
//    description->append("Kategoria: "+_f->cat.at(0).catname+"\n");
//    description->append("Alakategoria(t): ");
//    for (int w=0;w<_f->cat.at(0).subcats.size();w++)
//        description->append(_f->cat.at(0).subcats.at(w));
//    description->append("\n");
//    description->append("P‰iv‰ys: "+_f->date.toString("dd.MM.yyyy")+"\n");
//    description->append("Kuvaus: "+_f->description+"\n");
//    description->append("Kirjoittaja: "+_f->writer+"\n");
//    description->append("Kirjoitettu: "+_f->writedate.toString("dd.MM.yyyy")+"\n");

//    QLabel *information = new QLabel(*description, popup1);
//    information->setGeometry(QRect(20,50,289,200));
//    information->setWordWrap(1);

//    //QPixmap *image = new QPixmap("images/File.png");
//    QPixmap *image = new QPixmap("files/"+_f->name);
//    QLabel *imageLabel = new QLabel(popup1);
//    imageLabel->setPixmap(*image);
//    imageLabel->setGeometry(QRect(320, 40, 270, 200));

//    QPushButton *p= new QPushButton("Avaa",popup1);
//    p->setGeometry(QRect(200,250,90,30));
//    this->signalMapper->setMapping(p, _f->name);
//    connect(p, SIGNAL(clicked()), this->signalMapper, SLOT (map()));
//    connect(this->signalMapper, SIGNAL(mapped(const QString &)),
//                         this, SLOT(openfile(const QString &)));

//    QPushButton *pc= new QPushButton("Sulje",popup1);
//    pc->setGeometry(QRect(310,250,90,30));
//    connect(pc,SIGNAL(clicked()),popup1,SLOT(close()));

//    popup1->show();

//    return false;
}

void MainWindow::addCategoryButtons()
{
    QTreeWidgetItem *q, *qi;
    //searchWidget = new QTreeWidget(ui->centralWidget);
    q = this->ui->searchWidget->headerItem();
    q->setText(0,"Kategoriat");

    //this->ui->searchWidget->setGeometry(QRect(10, 40, 240, this->window_height-30));

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
    this->addButtons(list);
    tempFlag = true;
    this->ui->searchLineEdit->setText("Kirjoita hakusana");
    this->ui->searchLineEdit->setCursorPosition(0);
    tempFlag = false;

    if(this->dataCount > 50)
        this->ui->infoLabel->setText("KATEGORIA " + catname.toUpper() + ", NƒYTETƒƒN 50 KERRALLAAN"+ GetCriteriaText());
    else
        this->ui->infoLabel->setText("KATEGORIA " + catname.toUpper() + ", " + QString::number(this->dataCount) +" HAKUTULOSTA"+ GetCriteriaText());


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
        completer->preventSuggest();
        // update buttons in the main view
        QList <int> indexes = this->search->getIndexes(this->ui->searchLineEdit->text());
        //MainWindow *m = reinterpret_cast<MainWindow*> (this->parent());
        //qDebug() << "doSearch";
        this->addButtons(indexes);
        //QString url = QString(GSEARCH_URL).arg(text());
        //QDesktopServices::openUrl(QUrl(url));
        this->ui->infoLabel->setText("HAKUSANA " + this->ui->searchLineEdit->text().toUpper() + ", " + QString::number(this->dataCount) + " HAKUTULOSTA"+ GetCriteriaText());

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
    if(this->ui->searchLineEdit->text() != "" && this->ui->searchLineEdit->text() != "Kirjoita hakusana")
        doSearch();
    else if(this->ui->searchWidget->selectedItems().count() > 0)
        selectCategory(this->ui->searchWidget->selectedItems().first(),0 );
    else
    {
        QList <int> intlist;
        intlist.append(-1);
        addButtons(intlist);
    }

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
