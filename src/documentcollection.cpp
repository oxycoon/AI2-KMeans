#include "documentcollection.h"

DocumentCollection::DocumentCollection()
{
}

DocumentCollection::~DocumentCollection()
{
    _collection.clear();
}

std::vector<Document *> DocumentCollection::getCollection() const
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
