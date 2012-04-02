#include "search.h"

Search::Search()
{
}

void Search::addTag(QString &tagname, int fileidx)
{
    TagRefs t, tr;
    // Check if tag with the same name exists already
    if (!this->tags.isEmpty())
    {
        for (int i = 0; i<this->tags.length(); i++)
        {
            tr = this->tags.at(i);
            if (tr.tagname == tagname)
            {
                tr.filelist.append(fileidx);
                this->tags.replace(i,tr);
                return;
            }
        }
    }
    // this tag is not yet in the list, let's add
    t.tagname = tagname;
    t.filelist.append(fileidx);
    this->tags.append(t);

    // Order the tags list alphabetically
    QMap<QString, TagRefs> map;
    foreach (TagRefs tr, this->tags)
        map.insert(tr.tagname.toLower(), tr);
    this->tags = map.values();

    return;
}

QList <QString> Search::getTags()
{
    QList <QString> l;
    for (int i = 0; i<this->tags.length(); i++)
    {
        l.append(this->tags.at(i).tagname);
    }
    return l;
}

bool Search::sortByTagname(TagRefs *t1, TagRefs *t2)
{
     return t1->tagname < t2->tagname;
}

QList <TagRefs> Search::find(QString str)
{
    // return list of tags that match to str
    QList <TagRefs> tagrefs;
    QList <int> searchIdx;
    // Check if tag with the same name exists already
    if (!this->tags.isEmpty())
    {
        for (int i = 0; i<this->tags.length(); i++)
        {
            TagRefs tr = this->tags.at(i);
            if (tr.tagname.contains(str, Qt::CaseInsensitive))
            {
                tagrefs.append(tr);
                searchIdx.append(tr.filelist);
            }
        }
    }

    this->searchIndexes = searchIdx;
    return tagrefs;
}

QList <int> Search::getIndexes(QString str)
{
    this->find(str);
    return this->searchIndexes;
}


