#include "agent.h"

#include "document.h"

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
    initNonWords();
}

Agent::~Agent()
{
    for(int i = 0; i < _dataCollection.size(); i++)
    {
        delete _dataCollection[i];
    }

    _dataCollection.clear();
    _distinctTerms.clear();
    _nonWordList.clear();
}

double Agent::calcEuclDist(const std::vector<double> &vecA, const std::vector<double> &vecB)
{
    double result = 0;

    for(int i = 0; i < vecA.size(); i++)
    {
        result += std::pow(vecA[i] - vecB[i], 2);
    }
    return std::sqrt(result);
}

double Agent::findCosineSimilarity(const std::vector<double> &vecA, const std::vector<double> &vecB)
{
    double dotProduct = calcDotProduct(vecA, vecB);
    double magA = 0, magB = 0;

    magA = calcMagnitude(vecA);
    magB = calcMagnitude(vecB);

    if(magA == 0 || magB == 0)
        return 0.0;

    return dotProduct / (magA * magB);
}

std::vector<Centroid *> Agent::prepareDocumentCluster(int k, std::vector<Data *> &collection, int &counter)
{
    _globalCounter = 0;

    std::vector<Centroid*> centroids;
    Centroid* c;

    std::vector<int> uniqueRandoms;
    generateRandomNumbers(uniqueRandoms, k, collection.size());

    for(int i = 0; i < uniqueRandoms.size(); i++)
    {
        c = new Centroid();
        c->addDocument(collection[uniqueRandoms[i]]);
        centroids.push_back(c);
    }


    bool stopCrit;
    std::vector<Centroid*> result;
    std::vector<Centroid*> prevSet;

    do
    {
        prevSet = centroids;
        for(int i = 0; i < collection.size(); i++)
        {
            int index = findClosestCluster(centroids, collection[i]);
            result[index]->addDocument(collection[i]);
        }

    }while(!stopCrit);
}

std::vector<Data *> Agent::processDocuments(DocumentCollection &collection)
{
    std::vector<Document *> documents = collection.getCollection();

    //Find all distinct words in document collection.
    for(int i = 0; i < documents.size(); i++)
    {
        std::string text = documents[i]->getText();
        boost::algorithm::to_lower(text);

        std::stringstream ss(text);

        while(!ss.eof())
        {
            bool addToList = true;
            std::string word;
            ss >> word;

            //Removes punctuations and other symbols from the current word.
            int index;
            while ((index = word.find_first_of(".,!?\\;-*+")) != std::string::npos)
            {
                word.erase(index, 1);
            }

            //Checks if the word is something to ignore;
            for(int j = 0; j < _nonWordList.size(); j++)
            {
                if(word == _nonWordList[j])
                {
                    addToList = false;
                    continue;
                }
            }

            //If the word passed the non adding words test, check if
            //the word is already in the list
            if(addToList)
            {
                for(int j = 0; j < _distinctTerms.size(); j++)
                {
                    if(word == _distinctTerms[j])
                    {
                        addToList = false;
                        continue;
                    }
                }
            }

            if(addToList)
            {
                _distinctTerms.push_back(word);
            }
        }
    }

    //Remove unnecessary words and characters from the distinct terms list
    std::vector<std::string> killList = {"\"","\r","\n","(",")","[","]","{","}","","."," ",","};
    for(int i = 0; i < killList.size(); i++)
    {
        _distinctTerms.erase(std::remove(_distinctTerms.begin(), _distinctTerms.end(), killList[i]), _distinctTerms.end());
    }


    //DEBUG: _distinctTerms contents
    for(int i = 0; i < _distinctTerms.size(); i++)
    {
        std::cout << _distinctTerms[i] << std::endl;

    }

    //Create document vector space
    std::vector<Data *> result;
    Data* dv;
    std::vector<double> space;

    for(int i = 0; i < documents.size(); i++)
    {
        space.clear();
        for(int j = 0; j < _distinctTerms.size(); j++)
        {
            space.push_back(findTFIDF(documents[i], _distinctTerms[j]));
        }

        dv = new Data();
        dv->setContent(documents[i]->getText().c_str());
        dv->setVectorSpace(space);

    }

        //Calculate TFIDF per terms
        //Add document in vector space



    return result;
}

//------------------------------
//  PRIVATE FUNCTIONS - Initializers
//------------------------------

void Agent::initNonWords()
{
    _nonWordList.push_back("the");
    _nonWordList.push_back("a");
    _nonWordList.push_back("i");
    _nonWordList.push_back("and");
    _nonWordList.push_back("this");
    _nonWordList.push_back("is");
    _nonWordList.push_back("to");
    _nonWordList.push_back("or");
}

//------------------------------
//  PRIVATE FUNCTIONS
//------------------------------

double Agent::findTFIDF(Document *doc, std::string &term)
{
    double tf = findTermFrequency(doc, term);
    double idf = findInverseDocumentFrequency(term);

    return tf*idf;
}

double Agent::findTermFrequency(Document *doc, std::string &term)
{
    std::string temp = doc->getText();

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

//------------------------------
//  PRIVATE FUNCTIONS - helpers
//------------------------------

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

int Agent::findClosestCluster(const std::vector<Centroid *> clusterCenter, const Data * data)
{
    double similarity[clusterCenter.size()];

    for(int i = 0; i < clusterCenter.size(); i++)
    {
        similarity[i] = findCosineSimilarity(clusterCenter[i]->getDocuments()[0]->getVectorSpace(), data->getVectorSpace());
    }

}

/**
 * @brief Agent::calcDotProduct
 * @param vecA
 * @param vecB
 * @return
 *
 *  Calculates dot product of two vectors
 */
double Agent::calcDotProduct(const std::vector<double> &vecA, const std::vector<double> &vecB)
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
double Agent::calcMagnitude(const std::vector<double> &vector)
{
    return std::sqrt(calcDotProduct(vector, vector));
}

void Agent::generateRandomNumbers(std::vector<int> &set, const int k, const int docs)
{
    if(k > docs)
    {
        do
        {
            int pos = std::rand() % docs;
            if(!contains(set, pos))
                set.push_back(pos);
        }while(set.size() != docs);
    }
    else
    {
        do
        {
            int pos = std::rand() % docs;
            if(!contains(set, pos))
                set.push_back(pos);
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
    for(int i = 0; i < _nonWordList.size(); i++)
    {
        if(_nonWordList[i] == word)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Agent::contains
 * @param set
 * @param item
 * @return
 *
 *  Checks if the vector already contains this integer, used in the generation of random
 *  unique numbers.
 */
bool Agent::contains(const std::vector<int> &set, const int item)
{
    for(int i = 0; i < set.size(); i++)
    {
        if(set[i] == item)
            return true;
    }
    return false;
}
