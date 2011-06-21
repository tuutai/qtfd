#include <QLabel>
#include <QScrollArea>
#include <QDesktopServices>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xmlread.h"
#include "searchbox.h"
#include "timeline.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowTitle("T‰ss‰ on startWindow");

       showStartWindow();
       //this->centralWidget()->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showStartWindow()
{
     this->setWindowTitle("T‰ss‰ on title");
     this->window_width = 1000;
     this->window_height = 435;
     ui->setupUi(this);
    // this->centralWidget()->close();


     //QPalette paletti;
     //paletti.setBrush(this->backgroundRole(), QBrush(QImage("images/background.jpg")));
     //this->setPalette(paletti);

     goToBook = new QPushButton("Siirry historiikkiin",this);
     goToBook->setGeometry(QRect((this->width()/2-230), (this->height()/2-50), 200, 100));
     goToBook->show();
     QObject::connect(goToBook, SIGNAL(clicked()), this, SLOT(showBook()));

     goToTimeLine = new QPushButton("Siirry aikajanaan",this);
     goToTimeLine->setGeometry(QRect((this->width()/2+30), (this->height()/2-50), 200, 100));
     goToTimeLine->show();
     QObject::connect(goToTimeLine, SIGNAL(clicked()), this, SLOT(showTimeLine()));

}

void MainWindow::showBook()
{
    goToBook->close();
    goToTimeLine->close();
    this->centralWidget()->close();

    chapterOne = new QPushButton("1. Lestadiolaisuuden tulo ja alkuvaiheet 1870-1911",this);
    chapterOne->setGeometry(QRect(400, 100, 400, 35));
    chapterOne->show();
    QObject::connect(chapterOne, SIGNAL(clicked()), this, SLOT(showChapterOne()));

    chapterTwo = new QPushButton("Historiikin 2. luku",this);
    chapterTwo->setGeometry(QRect(400, 140, 150, 35));
    chapterTwo->show();
    QObject::connect(chapterTwo, SIGNAL(clicked()), this, SLOT(showBook()));

    chapterThree = new QPushButton("Historiikin 3. luku",this);
    chapterThree->setGeometry(QRect(400, 180, 150, 35));
    chapterThree->show();
    QObject::connect(chapterThree, SIGNAL(clicked()), this, SLOT(showBook()));

    chapterFour = new QPushButton("Historiikin 4. luku",this);
    chapterFour->setGeometry(QRect(400, 220, 150, 35));
    chapterFour->show();
    QObject::connect(chapterFour, SIGNAL(clicked()), this, SLOT(showBook()));

    chapterFive = new QPushButton("Historiikin 5. luku",this);
    chapterFive->setGeometry(QRect(400, 260, 150, 35));
    chapterFive->show();
    QObject::connect(chapterFive, SIGNAL(clicked()), this, SLOT(showBook()));

    chapterSix = new QPushButton("Historiikin 6. luku",this);
    chapterSix->setGeometry(QRect(400, 300, 150, 35));
    chapterSix->show();
    QObject::connect(chapterSix, SIGNAL(clicked()), this, SLOT(showBook()));

    chapterSeven = new QPushButton("Historiikin 7. luku",this);
    chapterSeven->setGeometry(QRect(400, 340, 150, 35));
    chapterSeven->show();
    QObject::connect(chapterSeven, SIGNAL(clicked()), this, SLOT(showBook()));

    chapterEight = new QPushButton("Historiikin 8. luku",this);
    chapterEight->setGeometry(QRect(400, 380, 150, 35));
    chapterEight->show();
    QObject::connect(chapterEight, SIGNAL(clicked()), this, SLOT(showBook()));

    chapterNine = new QPushButton("Historiikin 9. luku",this);
    chapterNine->setGeometry(QRect(400, 420, 150, 35));
    chapterNine->show();
    QObject::connect(chapterNine, SIGNAL(clicked()), this, SLOT(showBook()));

    changeButton = new QPushButton("Takaisin etusivulle",this);
    changeButton->setGeometry(QRect(840, 20, 150, 25));
    changeButton->show();
    QObject::connect(changeButton, SIGNAL(clicked()), this, SLOT(showStartWindow()));
}

void MainWindow::showChapterOne()
{
openfile("kirja/Luku_1.pdf");
}

void MainWindow::showTimeLine()
{

    timeLine();
}

void MainWindow::timeLine()
{
    goToBook->close();
    goToTimeLine->close();

    Timeline *Swidget; // Sisaltaa imagelabelin seka painonapit
    QScrollArea *scrollArea = ui->scrollArea;
    Swidget = new Timeline(scrollArea);

    scrollArea->setWidget(Swidget);

    this->xmlRead = new XMLRead();
    this->search = new Search();
    this->cats = new Categories();
    this->signalMapper = new QSignalMapper();
    this->widget = Swidget;
    this->xmlRead->readXML("meta.xml");

    qSort(this->xmlRead->files.begin(), this->xmlRead->files.end(), Files::fileLessThan);

    createTags();
    //qDebug() << this->search->getTags();
    QList <int> intlist;
    intlist.append(-1);
    this->widget->setGeometry(QRect(10, 10, this->window_width,this->window_height));
    this->flowLayout = new FlowLayout(this->widget, 4, 4);
    addButtons(intlist);

    QLinearGradient g(QPoint(0,0),QPoint(this->window_width,this->window_height));
    g.setColorAt(0,Qt::white);
    //g.setColorAt(0.5,Qt::yellow);
    g.setColorAt(1,Qt::darkGray);
    QPalette palette;
    palette.setBrush(QPalette::Window, g);
    Swidget->setPalette(palette);

    //this->searchbar = ui->lineEdit;

    SearchBox *searchEdit = new SearchBox(this->search, this);
    searchEdit->setGeometry(QRect(10, 20, 170, 25));
    searchEdit->show();

    addCategoryButtons();

    changeButton = new QPushButton("Takaisin etusivulle",this);
    changeButton->setGeometry(QRect(840, 20, 150, 25));
    changeButton->show();
    QObject::connect(changeButton, SIGNAL(clicked()), this, SLOT(showStartWindow()));
}

void MainWindow::addButtons(QList <int> indexes)
{
    QList<Files *> _files = this->xmlRead->files;
    //if (this->widget->layout()) delete this->widget->layout();
    //if (this->flowLayout->isEmpty())
    //{
    //        qDebug() << "layout is empty";
    //        delete this->flowLayout;
    //}

    buttonlist.clear();

    QLayoutItem *wItem;
    while ((wItem = this->widget->layout()->takeAt(0)) != 0)
          delete wItem->widget();

    FlowLayout *f = reinterpret_cast<FlowLayout*>(this->widget->layout());

    f->resetYearInfo();

    int x_offset = 0;
    int latest = 0;
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
        qDebug()<<buttonText;
        p= new QPushButton(*icon, buttonText,this->widget);
        //p = new QDocumentButton(*icon, buttonText,this->widget);
        qDebug()<<p->width();
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

        this->signalMapper->setMapping(p, f->name);
        QObject::connect(p, SIGNAL(clicked()), this->signalMapper, SLOT (map()));

        x_offset += 50;

        // Take first and last year for timeline
       if (oldest == 0 || f->year.toInt() < oldest) { oldest = f->year.toInt(); }
       if (latest == 0 || f->year.toInt() > latest) { latest = f->year.toInt(); }
    }

    int width = this->widget->width();

    //Piirret‰‰n v‰h‰n yli, ett‰ "tuoreimmat" napit mahtuvat n‰kyviin
    //Napit piirret‰‰n aina ko. vuodesta oikealle.

    qDebug()<<"Aikajanan aito pituus"<<latest-oldest;
    qDebug()<<"Aikajanan kasvatettu pituus"<<int((latest-oldest) * 1.2);
    latest = oldest + int((latest-oldest) * 1.2);
    qDebug()<<"Uusi latest"<<latest;

    flowLayout->setLayotInformation(oldest, latest, width);

    if (oldest != 0) { this->years.append(oldest); }
    if (latest != 0) { this->years.append(latest); }

    Timeline *t =   reinterpret_cast<Timeline*> (this->widget);
    t->updateYears(oldest, latest);

    this->widget->repaint();
    this->widget->setLayout(flowLayout);
flowLayout->update();
    QObject::connect(this->signalMapper, SIGNAL(mapped(const QString &)),
                     this, SLOT(openfile(const QString &)));
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

void MainWindow::addCategoryButtons()
{
    QTreeWidgetItem *q, *qi;
    searchWidget = new QTreeWidget(ui->centralWidget);
    q = searchWidget->headerItem();
    q->setText(0,"Kategoriat");

    //searchWidget->setGeometry(QRect(10, 80, 121, 271));
    searchWidget->setGeometry(QRect(10, 40, 170, 435));

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
        qi = new QTreeWidgetItem(searchWidget);
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
    connect(searchWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            SLOT(selectCategory(QTreeWidgetItem*,int)));
    searchWidget->show();
}

void MainWindow::selectCategory(QTreeWidgetItem* item,int n)
{
    QTreeWidgetItem* p = item->parent();
    QString parentname = "";
    QString catname = item->text(n);
    if (p) // parent found
        parentname = p->text(n);
        this->addButtons(this->cats->getIndexes(parentname,catname));
}
