#include "data.h"

Data::Data()
{
}

std::string Data::getContent()
{
    return _content;
}

void Data::setContent(const char *content)
{
    _content = content;
}

void Data::setVectorSpace(std::vector<double> vs)
{
    _vs = vs;
}

void Data::addDocumentCount(int count)
{
    _documentCount.push_back(count);
}

void Data::changeDocumentCount(int count, int index)
{
    _documentCount[index] = count;
}
