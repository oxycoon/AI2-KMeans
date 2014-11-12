#include "data.h"

Data::Data()
{
}

std::string Data::getContent()
{
    return _content;
}

std::vector<double> Data::getVectorSpace()
{
    return _vs;
}

void Data::setContent(const char *content)
{
    _content = content;
}

void Data::setVectorSpace(std::vector<double> vs)
{
    _vs = vs;
}
