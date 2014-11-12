#include "centroid.h"

#include <algorithm>̈́

Centroid::Centroid()
{
}

std::vector<Data *> Centroid::getDocuments()
{
    return _groupedDocuments;
}

void Centroid::setDocuments(std::vector<Data *> docs)
{
    _groupedDocuments = docs;
}

bool Centroid::addDocument(Data *doc)
{
    for(int i = 0; i < _groupedDocuments.size(); i++)
    {
        if(_groupedDocuments[i] == doc)
            return false;
    }
    _groupedDocuments.push_back(doc);
    return true;
}

bool Centroid::removeDocument(Data *doc)
{
    int elements = _groupedDocuments.size();
    _groupedDocuments.erase(std::remove(_groupedDocuments.begin(), _groupedDocuments.end(),
                                        doc), _groupedDocuments.end());
    return (elements > _groupedDocuments.size());
}
