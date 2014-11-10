#include "centroid.h"

Centroid::Centroid()
{
}

Centroid::Centroid(double x, double y)
{
    _x = x;
    _y = y;
}

double Centroid::getX()
{
    return _x;
}

double Centroid::getY()
{
    return _y;
}

void Centroid::setX(double x)
{
    _x = x;
}

void Centroid::setY(double y)
{
    _y = y;
}


