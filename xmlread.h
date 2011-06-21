#ifndef XMLREAD_H
#define XMLREAD_H

#include <QtXml>
#include "files.h"

class XMLRead
{
public:
    XMLRead();
    void readXML(QString _filename);
    QList<Files *> files;

private:
    void readFileMeta(QDomNode _file);
};


#endif // XMLREAD_H
