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

    this->setWindowTitle("T‰ss‰ on title");
    this->window_width = 1000;
    this->window_height = 435;
    ui->setupUi(this);

    //this->setAttribute(Qt::WA_NoSystemBackground);
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_OpaquePaintEvent);

    //QPalette paletti;
    //paletti.setBrush(this->backgroundRole(), QBrush(QImage("images/background.jpg")));
    //this->setPalette(paletti);

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
    this->timewidget = new QWidget(scrollArea);

    this->timewidget->setStyleSheet("background:green;");

    qSort(this->xmlRead->files.begin(), this->xmlRead->files.end(), Files::fileLessThan);

    createTags();
    //qDebug() << this->search->getTags();
    QList <int> intlist;
    intlist.append(-1);
    this->widget->setGeometry(QRect(10, 10, this->window_width,this->window_height));
    this->flowLayout = new FlowLayout(this->widget, 4, 4);
    addButtons(intlist);

    this->timewidget->setGeometry(QRect(0, this->window_height-60, this->window_width,50));
    this->timewidget->setWhatsThis("TIMEWIDGET");

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


}

MainWindow::~MainWindow()
{
    delete ui;
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
