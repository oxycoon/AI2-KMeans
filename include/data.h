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

    void setContent(const char* content);
    void setVectorSpace(std::vector<double> vs);

    void addDocumentCount(int count);
    void changeDocumentCount(int count, int index);


protected:

private:

    std::vector<double> _documentCount;
    std::vector<double> _vs;

    std::string _content;


};

#endif // DATA_H
