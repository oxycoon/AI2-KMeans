#ifndef DATA_H
#define DATA_H

#include "document.h"

#include <string>
#include <vector>

class Data
{
public:
    Data();
    Data(double x, double y);
    Data(char* content);

    double getX();
    double getY();
    std::string getContent();

    void setX(double x);
    void setY(double y);
    void setContent(char* content);

    void addDocumentCount(int count);
    void changeDocumentCount(int count, int index);


protected:

private:
    double _x, _y;

    std::vector<double> _documentCount;

    std::string _content;


};

#endif // DATA_H
