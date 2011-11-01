#include <QFile>
#include <QtDebug>
#include "xmlread.h"

XMLRead::XMLRead()
{
}

void XMLRead::readXML(QString _filename)
{
    QDomDocument doc("xmlfile");
    QFile file(_filename);
    if (!file.open(QIODevice::ReadOnly)) return;
    QString errors = "";
    if (!doc.setContent(&file,false,&errors))
    {
        file.close();
        qDebug() << "file closed, errors: " << errors;
        return;
    }
    file.close();
    QDomElement docElem = doc.documentElement();
    QDomNodeList nodeList = docElem.elementsByTagName("file");
//    qDebug() << "nodeList.count(): " << nodeList.count();
    if (nodeList.count() > 0)
    {
        for(int iDx = 0;iDx < nodeList.count(); iDx++)
        {
            //qDebug() << nodeList.at(iDx).nodeName();
            readFileMeta(nodeList.at(iDx));
        }
    }
}

void XMLRead::readFileMeta(QDomNode _file)
{
    Files *f = new Files();
    QDomNodeList childs = _file.childNodes();
    for(int iDx = 0;iDx < childs.count(); iDx++)
    {
        QString nodename = childs.at(iDx).nodeName();
  //      qDebug() << nodename;
        if (nodename == "name")
        {
            //qDebug() << nodename << " = " << childs.at(iDx).toElement().text();
            f->name = childs.at(iDx).toElement().text();
        }
        else if (nodename == "year" )
        {
            //qDebug() << nodename << " = " << childs.at(iDx).toElement().text();
            f->year = childs.at(iDx).toElement().text();
        }
        else if (nodename == "date" )
        {
            //qDebug() << nodename << " = " << childs.at(iDx).toElement().text();
            QDate date = QDate::fromString(childs.at(iDx).toElement().text(),"d.M.yyyy");
            f->date = date;
            f->year = date.toString("yyyy");
            //qDebug() << f->date;
        }
        else if (nodename == "categories" )
        {
            //qDebug() << nodename << " = " << childs.at(iDx).toElement().text();
            QDomNodeList catlist = childs.at(iDx).childNodes();
            for(int r = 0;r < catlist.count(); r++)
            {
                Category temp_category;
                QDomNodeList cat = catlist.at(r).childNodes();
                QString catname = "";
                for(int p = 0;p < cat.count(); p++)
                {
                    if (cat.at(p).nodeName() == "catname")
                    {
                        catname = cat.at(p).toElement().text();
                        temp_category.catname = catname;
                    }
                    else if (cat.at(p).nodeName() == "subcategories")
                    {
                        QDomNodeList subcatnames = cat.at(p).childNodes();
                        for(int t = 0;t < subcatnames.count(); t++)
                        {
                            QString scatname = subcatnames.at(t).toElement().text();
                            temp_category.subcats.append(scatname);
                            //qDebug() << scatname;
                        }
                        //qDebug() << temp_category.subcats;
                    }
                }
                //qDebug() << temp_category.catname << temp_category.subcats;
                f->cat.append(temp_category);
            }

        }
        else if (nodename == "topic" )
        {
            //qDebug() << nodename << " = " << childs.at(iDx).toElement().text();
            f->topic = childs.at(iDx).toElement().text();
        }
        else if (nodename == "description" )
        {
            //qDebug() << nodename << " = " << childs.at(iDx).toElement().text();
            f->description = childs.at(iDx).toElement().text();
        }
        else if (nodename == "writer" )
        {
            //qDebug() << nodename << " = " << childs.at(iDx).toElement().text();
            f->writer = childs.at(iDx).toElement().text();
        }
        else if (nodename == "writedate" )
        {
            //qDebug() << nodename << " = " << childs.at(iDx).toElement().text();
            QDate date = QDate::fromString(childs.at(iDx).toElement().text(),"dd.MM.yyyy");
            f->writedate = date;
        }
        else if (nodename == "searchtags" )
        {
            //qDebug() << nodename << " = " << childs.at(iDx).toElement().text();
            QDomNodeList taglist = childs.at(iDx).childNodes();
            QList <QString> tags;
            for(int r = 0;r < taglist.count(); r++)
            {
                tags.append(taglist.at(r).toElement().text());
            }
            f->tags = tags;
            //qDebug() << f->tags;
        }

    }
    files.append(f);
}
