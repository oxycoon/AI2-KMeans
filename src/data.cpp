#include "data.h"

Data::Data()
{
}

std::string Data::getContent() const
{
    return _content;
}

std::string Data::getFileName() const
{
    return _fileName;
}

std::vector<double> Data::getVectorSpace() const
{
    return _vs;
}

void Data::setContent(const char *content)
{
    _content = content;
}

void Data::setFileName(const char *name)
{
    _fileName = name;
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
