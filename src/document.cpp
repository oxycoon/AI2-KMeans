#include "document.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/algorithm/string.hpp>

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
    _path = path;
    boost::algorithm::to_lower(_text);

    _wordCount = countWords(_text.c_str());
}

Document::~Document()
{

}

std::string Document::getText() const
{
    return _text;
}

std::string Document::getPath() const
{
    return _path;
}

int Document::getWordCount() const
{
    return _wordCount;
}

int Document::getTermCount(const std::string &term)
{
    std::string temp = term;

    if(_wordList.find(temp) != _wordList.end())
    {
        return _wordList[temp];
    }
    else
    {
        return 0;
    }
}

/**
 * @brief Agent::countWords
 * @param str
 * @return
 *
 *  http://stackoverflow.com/questions/3672234/c-function-to-count-all-the-words-in-a-string
 */
int Document::countWords(const std::string &text)
{

    std::string currentWord;

    std::stringstream stream(text);
    while(stream >> currentWord)
    {
        int index;
        while ((index = currentWord.find_first_of(".,!?\\;-*+")) != std::string::npos)
        {
            currentWord.erase(index, 1);

            if(_wordList.find(currentWord) != _wordList.end())
            {
                _wordList[currentWord]++;
            }
            else
            {
               _wordList[currentWord] = 1;
            }
        }
        //++_wordList[currentWord];
        _wordCount++;
    }



    /*bool inSpaces = true;
    int words = 0;

    while(*str != NULL)
    {
        if(std::isspace(*str))
        {
            inSpaces = true;
        }
        else if(inSpaces)
        {
            words++;
            inSpaces = false;
        }
        ++str;
    }
    return words;*/

}
