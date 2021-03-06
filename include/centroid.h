#ifndef CENTROID_H
#define CENTROID_H

#include <string>
#include <vector>

#include "data.h"

class Centroid
{
public:
    Centroid();
    ~Centroid();

    std::vector<Data*> getDocuments() const;
    int getSize() const;

    void setDocuments(std::vector<Data*> docs);


    bool addDocument(Data* doc);
    bool removeDocument(Data* doc);

    void clearGroupedDocuments();
    void printGroup();

private:
    std::vector<Data*> _groupedDocuments;
};

#endif // CENTROID_H
