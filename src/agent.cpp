#include "agent.h"

#include <algorithm>̈́
#include <map>
#include <sstream>
#include <iostream>

#include <boost/algorithm/string.hpp>





Agent::Agent()
{

}

double Agent::findTFIDF(Data *doc, std::string &term)
{
    double tf = findTermFrequency(doc, term);
    double idf = findInverseDocumentFrequency(term);

    return tf*idf;
}

double Agent::findTermFrequency(Data *doc, std::string &term)
{
    std::string temp = doc->getContent();

    //Converts the text and term to lowercase for easy comparison
    boost::algorithm::to_lower(temp);
    boost::algorithm::to_lower(term);

    int termCount, wordCount;

    termCount = countTermWords(temp, term);
    wordCount = countWords(temp.c_str());

    return (double)termCount / (double)wordCount;
}

double Agent::findInverseDocumentFrequency(const std::string &term)
{

}

/**
 * @brief Agent::countWords
 * @param str
 * @return
 *
 *  http://stackoverflow.com/questions/3672234/c-function-to-count-all-the-words-in-a-string
 */
int Agent::countWords(const char *str)
{
    bool inSpaces = true;
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
    return words;
}

/**
 * @brief Agent::countTermWords
 * @param text
 * @param term
 * @return
 */
int Agent::countTermWords(const std::string &text, const std::string &term)
{
    std::map<std::string, int> words;

    std::string currentWord;
    words[term] = 0;

    std::stringstream stream(text);
    while(stream >> currentWord)
    {
        int index;
        while ((index = currentWord.find_first_of(".,!?\\;-*+")) != std::string::npos)
        {
            currentWord.erase(index, 1);
        }
        ++words[currentWord];
    }



    return words[term];
}
