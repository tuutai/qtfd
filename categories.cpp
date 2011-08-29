#include "categories.h"

Categories::Categories()
{
}

QList <QString> Categories::getCats()
{
    category cat;
    QList <QString> stringlist;
    for (int i = 0; i<this->categories.length(); i++)
    {
        cat = this->categories.at(i);
        stringlist.append(cat.parentcat.tagname);
    }
    return stringlist;
}

//No niin.
//joo.
QList <QString> Categories::getSubCats(QString parent)
{
    category cat;
    QList <QString> stringlist;
    for (int i = 0; i<this->categories.length(); i++)
    {
        cat = this->categories.at(i);
        if (cat.parentcat.tagname == parent)
        {
            // This is the correct parent category
            TagRefs tr;

            //Find if this subcategory exists already
            for (int i2 = 0; i2<cat.subcats.length(); i2++)
            {
                tr = cat.subcats.at(i2);
                stringlist.append(tr.tagname);
            }
        }
    }
    return stringlist;
}

void Categories::addCat(QString &parent,QString &catname, int fileidx)
{
    category c, cat;

    // Remove whitespaces, put category to lowercase
    catname = catname.trimmed().toLower();
    // Uppercase character first
    if (catname.size() != 0)
        catname = catname.at(0).toUpper() + catname.mid(1);

    // debug catch point
    if (fileidx == 3)
        int i = 0;

    // First check if this is parent category
    if (parent.isEmpty())
    {
        //Find if this category exists already
        for (int i = 0; i<this->categories.length(); i++)
        {
            cat = this->categories.at(i);
            if (cat.parentcat.tagname == catname)
            {
                // adding a file reference to parent category
                cat.parentcat.filelist.append(fileidx);
                this->categories.replace(i,cat);
                return;
            }
        }
        // category does not exist, create a new
        c.parentcat.tagname = catname;
        c.parentcat.filelist.append(fileidx);
        this->categories.append(c);

        // Order the categories list alphabetically
        QMap<QString, category> map;
        foreach (category _cat, this->categories)
            map.insert(_cat.parentcat.tagname.toLower(), _cat);
        this->categories = map.values();
        return;
    }
    else
    {
        //This is subcategory
        for (int i = 0; i<this->categories.length(); i++)
        {
            cat = this->categories.at(i);
            if (cat.parentcat.tagname == parent)
            {
                // This is the correct parent category
                TagRefs tr,tr2;

                //Find if this subcategory exists already
                for (int i2 = 0; i2<cat.subcats.length(); i2++)
                {
                    tr = cat.subcats.at(i2);
                    if (tr.tagname == catname)
                    {
                        // adding a file reference to existing subcategory
                        tr.filelist.append(fileidx);
                        this->categories[i].subcats.replace(i2,tr);
                        return;
                    }
                }
                // subcategory does not exist, create a new
                tr2.tagname = catname;
                tr2.filelist.append(fileidx);
                this->categories[i].subcats.append(tr2);

                // Order the categories list alphabetically
                QMap<QString, TagRefs> map;
                foreach (TagRefs tr3, this->categories.at(i).subcats)
                    //map.insert(tr3.tagname.toLower(), tr3);
                    map.insert(tr3.tagname, tr3);
                this->categories[i].subcats = map.values();
                return;
            }
        }
    }
    return;
}

QList <int> Categories::getIndexes(QString parentname, QString catname)
{
    category cat;
    QList <int> empty;
    //Find this category
    for (int i = 0; i<this->categories.length(); i++)
    {
        cat = this->categories.at(i);
        if (cat.parentcat.tagname == catname)
        {
            // this is parent level category
            // return file list matching to this category
            return cat.parentcat.filelist;
        }
        // Check also subcats of this category ir name marches with parent
        if (cat.parentcat.tagname == parentname)
        {
        foreach (TagRefs tr, this->categories.at(i).subcats)
            if (tr.tagname == catname)
                return tr.filelist;
        }
    }
    return empty;
}
