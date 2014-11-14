#include "centroid.h"

#include <algorithm>̈́
#include <iostream>

Centroid::Centroid()
{
}

Centroid::~Centroid()
{
    clearGroupedDocuments();
}

/**
 * @brief Centroid::getDocuments
 * @return
 *
 *  Gets grouped document list
 */
std::vector<Data *> Centroid::getDocuments() const
{
    return _groupedDocuments;
}

/**
 * @brief Centroid::setDocuments
 * @param docs
 *
 *  Sets the grouped document list
 */
void Centroid::setDocuments(std::vector<Data *> docs)
{
    _groupedDocuments = docs;
}

/**
 * @brief Centroid::getSize
 * @return
 *
 *  Gets the amount of documents in the document list.
 */
int Centroid::getSize() const
{
    return _groupedDocuments.size();
}

/**
 * @brief Centroid::addDocument
 * @param doc
 * @return
 *
 *  Adds a new document to the list if it's not already
 *  listed
 */
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

/**
 * @brief Centroid::removeDocument
 * @param doc
 * @return
 *
 *  Removes specified document from the list, returns false if document
 *  was not found.
 */
bool Centroid::removeDocument(Data *doc)
{
    int elements = _groupedDocuments.size();
    _groupedDocuments.erase(std::remove(_groupedDocuments.begin(), _groupedDocuments.end(),
                                        doc), _groupedDocuments.end());
    return (elements > _groupedDocuments.size());
}

/**
 * @brief Centroid::clearGroupedDocuments
 *
 *  Clears the grouped document list
 */
void Centroid::clearGroupedDocuments()
{
    _groupedDocuments.clear();
}

/**
 * @brief Centroid::printGroup
 *
 *  Prints which documents are tied to this centroid
 */
void Centroid::printGroup()
{
    for(int i = 0; i < _groupedDocuments.size(); i++)
    {
        std::cout << _groupedDocuments[i]->getFileName() << std::endl;
    }
}
