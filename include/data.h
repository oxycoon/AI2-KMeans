#ifndef DATA_H
#define DATA_H

#include "document.h"

#include <string>
#include <vector>

class Data
{
public:
    Data();

    std::string getContent();
    std::vector<double> getVectorSpace();

    void setContent(const char* content);
    void setVectorSpace(std::vector<double> vs);

private:
    std::vector<double> _vs;
    std::string _content;


};

#endif // DATA_H
