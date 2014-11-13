#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <string>

class Filter
{
public:
    Filter();

    std::vector<std::string> getFilter() const;
    std::string getName() const;

protected:
    std::vector<std::string> _filter;
    std::string _name;
};

#endif // FILTER_H
