#include "agent.h"

#include <algorithm>̈́
#include <cmath>
#include <map>
#include <sstream>
#include <iostream>
#include <numeric>

#include <time.h>
#include <stdlib.h>


#include <boost/algorithm/string.hpp>





Agent::Agent()
{
    srand (time(NULL));

}

double Agent::calcEuclDist(std::vector<double> vecA, std::vector<double> vecB)
{
    double result = 0;

    for(int i = 0; i < vecA.size(); i++)
    {
        result += std::pow(vecA[i] - vecB[i], 2);
    }
    return std::sqrt(result);
}

double Agent::findCosineSimilarity(std::vector<double> vecA, std::vector<double> vecB)
{
    double dotProduct = calcDotProduct(vecA, vecB);
    double magA = 0, magB = 0;

    magA = calcMagnitude(vecA);
    magB = calcMagnitude(vecB);

    if(magA == 0 || magB == 0)
        return 0.0;

    return dotProduct / (magA * magB);
}

std::vector<Data *> Agent::prepareDocumentCluster(int k, std::vector<Data *> collection, int counter)
{
    _globalCounter = 0;

    std::vector<Centroid> centroids;
    Centroid c;

    std::unordered_set<int> set;
}

std::vector<Data *> Agent::processDocuments(std::vector<Data *> dataCollection)
{
    //Find all distinct words in document collection.

    //Remove white spaces, punctuations etc

    //Create document vector space

        //Calculate TFIDF per terms
        //Add document in vector space

    std::vector<Data *> collection;

    return collection;
}

void Agent::initNonWords()
{
    _nonWordList.push_back("the");
    _nonWordList.push_back("a");
    _nonWordList.push_back("i");
    _nonWordList.push_back("and");
}

//------------------------------
//  PRIVATE FUNCTIONS
//------------------------------

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
    int documentCount = 0;

    for(int i = 0; i < _dataCollection.size(); i++)
    {
        std::string temp = _dataCollection[i]->getContent();
        std::string tempTerm = term;

        boost::algorithm::to_lower(temp);
        boost::algorithm::to_lower(tempTerm);

        if(countTermWords(temp, tempTerm) > 0)
        {
            documentCount++;
        }
    }

    if(documentCount > 0)
        return (double)std::log((double)(_dataCollection.size())/(double)documentCount);
    else
        return 0;
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

/**
 * @brief Agent::calcDotProduct
 * @param vecA
 * @param vecB
 * @return
 *
 *  Calculates dot product of two vectors
 */
double Agent::calcDotProduct(std::vector<double> vecA, std::vector<double> vecB)
{
    double result = 0;

    for(int i = 0; i < vecA.size(); i++)
    {
        result += vecA[i] * vecB[i];
    }
    return result;
}

/**
 * @brief Agent::calcMagnitude
 * @param vector
 * @return
 *
 *  Calculates length of vector
 */
double Agent::calcMagnitude(std::vector<double> vector)
{
    return std::sqrt(calcDotProduct(vector, vector));
}

void Agent::generateRandomNumbers(std::unordered_set<int> &set, int k, int docs)
{
    if(k > docs)
    {
        do
        {
            int pos = std::rand() % docs;
            set.insert(pos);
        }while(set.size() != docs);
    }
    else
    {
        do
        {
            int pos = std::rand() % docs;
            set.insert(pos);
        }while(set.size() != k);
    }
}

/**
 * @brief Agent::checkForNonWord
 * @param word
 * @return
 *
 *  Checks if the word in question is a word that should not be counted.
 */
bool Agent::checkForNonWord(const char *word)
{
    bool result = false;
    for(int i = 0; i < _nonWordList.size(); i++)
    {
        if(_nonWordList[i] == word)
        {
            result = true;
            break;
        }
    }
    return result;
}
