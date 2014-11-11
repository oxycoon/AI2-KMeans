#include "documentcollection.h"

DocumentCollection::DocumentCollection()
{
}

std::vector<Document *> DocumentCollection::getCollection()
{
    return _collection;
}

void DocumentCollection::addDocument(Document *doc)
{
    bool contains = false;

    for(int i = 0; i < 0; i++)
    {
        if(_collection[i] == doc)
        {
            contains = true;
            break;
        }
    }

    if(!contains)
        _collection.push_back(doc);
}
