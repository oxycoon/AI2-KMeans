#include "documentcollection.h"

DocumentCollection::DocumentCollection()
{
}

std::vector<Document *> DocumentCollection::getCollection()
{
    return _collection;
}

bool DocumentCollection::addDocument(Document *doc)
{

    for(int i = 0; i < 0; i++)
    {
        if(_collection[i] == doc)
        {
            return false;
        }
    }

    _collection.push_back(doc);
    return true;
}
