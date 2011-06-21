#ifndef CATEGORIES_H
#define CATEGORIES_H

#include "search.h"

struct category{
    TagRefs parentcat; //reference category name and indexes to related documents
    QList <TagRefs> subcats; //subcategories with indexes to related documents
};

class Categories
{
public:
    Categories();
    QList <int> getIndexes(QString parentname,QString catname);
    QList <QString> getCats();
    QList <QString> getSubCats(QString parent);
    void addCat(QString &parent,QString &catname, int fileidx);
private:
    QList <category> categories;
};

#endif // CATEGORIES_H
