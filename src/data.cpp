#include "data.h"

Data::Data()
{
}

std::string Data::getContent() const
{
    return _content;
}

std::vector<double> Data::getVectorSpace() const
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

void Data::setVectorSpaceAt(double value, int index)
{
    if(index < _vs.size())
        _vs[index] = value;
}
