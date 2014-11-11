#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>


class Document
{
public:
    Document(const char* path);

    std::string getText();

private:
    std::string _text;
    std::string _path;
};

#endif // DOCUMENT_H
