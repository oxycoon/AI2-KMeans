#ifndef DATA_H
#define DATA_H

#include "document.h"

#include <string>
#include <vector>

class Data
{
public:
    Data();

    std::string getContent() const;
    std::string getFileName() const;
    std::vector<double> getVectorSpace() const;

    void setContent(const char* content);
    void setFileName(const char* name);
    void setVectorSpace(std::vector<double> vs);
    void setVectorSpaceAt(double value, int index);

private:
    std::vector<double> _vs;
    std::string _content;
    std::string _fileName;


};

#endif // DATA_H
