#include "document.h"

#include <iostream>
#include <fstream>

Document::Document(const char *path)
{
    std::ifstream file;

    file.open(path);

    if(file.is_open())
    {
        _path = path;
        std::string line;
        while(std::getline(file, line))
        {
            _text.append(line);
            _text.append("\n");
        }
    }
    file.close();
}

std::string Document::getText()
{
    return _text;
}
