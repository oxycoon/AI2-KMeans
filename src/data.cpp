#include "data.h"

Data::Data()
{
}

Data::Data(double x, double y)
{
    _x = x;
    _y = y;
}

Data::Data(char *content)
{
    _content = content;
}

double Data::getX()
{
    return _x;
}

double Data::getY()
{
    return _y;
}

std::string Data::getContent()
{
    return _content;
}

void Data::setX(double x)
{
    _x = x;
}

void Data::setY(double y)
{
    _y = y;
}

void Data::setContent(char *content)
{
    _content = content;
}

void Data::addDocumentCount(int count)
{
    _documentCount.push_back(count);
}

void Data::changeDocumentCount(int count, int index)
{
    _documentCount[index] = count;
}
