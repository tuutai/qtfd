#include "files.h"

Files::Files()
{
}

bool Files::fileLessThan(Files *f1, Files *f2)
{
     return f1->date < f2->date;
}
