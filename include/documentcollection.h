#ifndef DOCUMENTCOLLECTION_H
#define DOCUMENTCOLLECTION_H

#include "document.h"

#include <vector>

class DocumentCollection
{
public:
    DocumentCollection();
    ~DocumentCollection();

    std::vector<Document*> getCollection() const;

    bool addDocument(Document* doc);

private:
    std::vector<Document*> _collection;
};

#endif // DOCUMENTCOLLECTION_H
