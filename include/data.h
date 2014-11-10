#ifndef DATA_H
#define DATA_H

#include <string>

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


protected:

private:
    double _x, _y;

    std::string _content;


};

#endif // DATA_H
