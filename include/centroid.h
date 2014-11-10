#ifndef CENTROID_H
#define CENTROID_H

#include <string>
#include <vector>

#include "data.h"

class Centroid
{
public:
    Centroid();
    Centroid(double x, double y);

    double getX();
    double getY();

    void setX(double x);
    void setY(double y);

    //std::vector<Data*> prepareDocumentCluster(int k, std::vector<Data*> collection, int counter);

private:
    double _x, _y;

    std::vector<Data*> _groupedDocuments;
};

#endif // CENTROID_H
