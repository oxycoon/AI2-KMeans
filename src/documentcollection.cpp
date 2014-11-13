#include "documentcollection.h"

DocumentCollection::DocumentCollection()
{
}

DocumentCollection::~DocumentCollection()
{
    /*for(int i = 0; i < _collection.size(); i++)
    {
        delete _collection[i];
    }*/
    /*while(!_collection.empty())
    {
        Document *el = _collection.back();
        _collection.pop_back();
        delete el;
    }*/

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
