#include "filter.h"

Filter::Filter()
{
}

std::vector<std::string> Filter::getFilter() const
{
    return _filter;
}

std::string Filter::getName() const
{
    return _name;
}
