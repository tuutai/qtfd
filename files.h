#ifndef FILES_H
#define FILES_H

#include <QtCore>

struct Category
{
    QString catname;
    QList <QString> subcats;
};

class Files
{
public:
    Files();
    QString name;
    QString year;
    QDate date;
    QList <Category> cat;
    QString topic;
    QString description;
    QString writer;
    QDate writedate;
    QList <QString> tags;
    static bool fileLessThan(Files *f1, Files *f2);
};

#endif // FILES_H
