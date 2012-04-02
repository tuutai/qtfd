#ifndef SEARCH_H
#define SEARCH_H

#include <QtCore>

struct SearchCriteria
{
    bool showVideo;
    bool showAani;
    bool showArtikkeli;
    bool showKuva;
};

struct TagRefs
{
    QString tagname; // tag name
    QList <int> filelist; // files matching to this tag
    QList <int> GetFilteredFileList(SearchCriteria crit);
    // this number refers to file index position in main files list
};


class Search
{
public:
    Search();
    void addTag(QString &tagname, int fileidx);
    QList <QString> getTags();
    QList <TagRefs> find(QString str);
    QList <int> getIndexes(QString str);
private:
    QList <TagRefs> tags;
    bool sortByTagname(TagRefs *t1, TagRefs *t2);
    QList <int> searchIndexes;
};

#endif // SEARCH_H
