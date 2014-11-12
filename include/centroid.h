#ifndef CENTROID_H
#define CENTROID_H

#include <string>
#include <vector>

#include "data.h"

class Centroid
{
public:
    Centroid();

    std::vector<Data*> getDocuments();
    void setDocuments(std::vector<Data*> docs);

    bool addDocument(Data* doc);
    bool removeDocument(Data* doc);

private:
    std::vector<Data*> _groupedDocuments;
};

#endif // CENTROID_H
