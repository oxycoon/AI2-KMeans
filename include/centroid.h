#ifndef CENTROID_H
#define CENTROID_H

#include <string>

class Centroid
{
public:
    Centroid();
    Centroid(double x, double y);

    double getX();
    double getY();

    void setX(double x);
    void setY(double y);

private:
    double _x, _y;

    std::string _content;
};

#endif // CENTROID_H
