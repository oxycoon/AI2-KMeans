#include "agent.h"

#include "document.h"
#include "filter.h"

#include "MatchPathSeparator.h"

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

double Agent::calcCosineSimilarity(const std::vector<double> &vecA, const std::vector<double> &vecB)
{
    double dotProduct = calcDotProduct(vecA, vecB);
    double magA = 0, magB = 0;

    magA = calcMagnitude(vecA);
    magB = calcMagnitude(vecB);

    if(magA == 0 || magB == 0)
        return 0.0;

    return dotProduct / (magA * magB);
}

/**
 * @brief Agent::prepareDocumentCluster
 * @param k
 * @param collection
 * @param counter
 * @return
 *
 *  Creates the clusters using randomized initial centroids with k clusters
 */
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

        initClusterCenter(centroids, centroids.size());
        centroids = calcMeanPoints(result);
        stopCrit = checkStopCrit(prevSet, centroids);

        if(!stopCrit)
            initClusterCenter(result, centroids.size());

    }while(!stopCrit);

    counter = _counter;
    return result;
}

/**
 * @brief Agent::prepareDocumentCluster
 * @param collection
 * @param seeds
 * @return
 *
 *  Creates the clusters using seeds as initial centroids
 */
std::vector<Centroid *> Agent::prepareDocumentCluster(std::vector<Data*> &collection, std::vector<Data*> &seeds, int &counter)
{
    _globalCounter = 0;

    std::vector<Centroid*> centroids;
    Centroid* c;

    for(int i = 0; i < seeds.size(); i++)
    {
        c = new Centroid();
        c->addDocument(seeds[i]);
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

        initClusterCenter(centroids, centroids.size());
        centroids = calcMeanPoints(result);
        stopCrit = checkStopCrit(prevSet, centroids);

        if(!stopCrit)
            initClusterCenter(result, centroids.size());

    }while(!stopCrit);

    counter = _counter;
    return result;
}

std::vector<Data *> Agent::processDocuments(DocumentCollection &collection)
{
    //std::vector<Document *> documents = collection.getCollection();
    _documentCollection = collection;

    //Find all distinct words in document collection.
    for(int i = 0; i < collection.getCollection().size(); i++)
    {
        std::string text = collection.getCollection()[i]->getText();
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

    //Create document vector space
    std::vector<Data *> result;
    Data* dv;

    for(int i = 0; i < collection.getCollection().size(); i++)
    {
        std::vector<double> space;
        //Calculate TFIDF per terms and add document in vector space

        for(int j = 0; j < _distinctTerms.size(); j++)
        {
            space.push_back(findTFIDF(collection.getCollection()[i], _distinctTerms[j]));
        }
        dv = new Data();
        dv->setContent(collection.getCollection()[i]->getText().c_str());
        dv->setVectorSpace(space);
        dv->setFileName(collection.getCollection()[i]->getPath().c_str());
        result.push_back(dv);
    }
    return result;
}

std::vector<Data *> Agent::processDocuments(DocumentCollection &collection, const std::vector<Filter*> &filter)
{
    _documentCollection = collection;

    //Adds the filter words to the distinct words list
    {
        bool alreadyInList = false;
        for(int i = 0; i < filter.size(); i++)
        {
            for(int j = 0; j < filter[i]->getFilter().size(); j++)
            {
                //If there are multiple occurances of the same filter word
                //don't add more than once
                for(int k = 0; k < _distinctTerms.size(); k++)
                {
                    if(_distinctTerms[k] == filter[i]->getFilter()[j])
                        alreadyInList = true;
                }
                if(!alreadyInList)
                    _distinctTerms.push_back(filter[i]->getFilter()[j]);
            }
        }
    }

    //Create document vector space
    std::vector<Data *> result;
    Data* dv;

    for(int i = 0; i < collection.getCollection().size(); i++)
    {
        std::vector<double> space;
        //Calculate TFIDF per terms and add document in vector space

        for(int j = 0; j < _distinctTerms.size(); j++)
        {
            space.push_back(findTFIDF(collection.getCollection()[i], _distinctTerms[j]));
        }
        dv = new Data();
        dv->setContent(collection.getCollection()[i]->getText().c_str());
        dv->setVectorSpace(space);
        dv->setFileName(collection.getCollection()[i]->getPath().c_str());
        result.push_back(dv);
    }
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

void Agent::initClusterCenter(std::vector<Centroid *> &centroids, int size)
{
    Centroid* c;
    centroids.clear();

    for(int i = 0; i < size; i++)
    {
        c = new Centroid();
        centroids.push_back(c);
    }
}

//------------------------------
//  PRIVATE FUNCTIONS
//------------------------------

double Agent::findTFIDF(Document *doc, std::string &term)
{
    double tf = findTermFrequency(doc, term);
    double idf = findInverseDocumentFrequency(term);

    //DEBUG:
    //std::cout << tf << ", " << idf << std::endl;

    return tf*idf;
}

double Agent::findTermFrequency(Document *doc, std::string &term)
{
    std::string temp = doc->getText();

    //Converts the text and term to lowercase for easy comparison
    boost::algorithm::to_lower(temp);
    boost::algorithm::to_lower(term);

    int termCount, wordCount;

    termCount = doc->getTermCount(term);
    wordCount = doc->getWordCount();

    return (double)termCount / (double)wordCount;
}

double Agent::findInverseDocumentFrequency(const std::string &term)
{
    int documentCount = 0;

    //DEBUG:
    //std::cout << _documentCollection.getCollection().size() << std::endl;
    for(int i = 0; i < _documentCollection.getCollection().size(); i++)
    {
        //std::string temp = _documentCollection.getCollection()[i]->getText();
        std::string tempTerm = term;

        /*boost::algorithm::to_lower(temp);
        boost::algorithm::to_lower(tempTerm);*/

        //DEBUG:
        //std::cout << term << ": " << countTermWords(temp, tempTerm) << std::endl;
        if(_documentCollection.getCollection()[i]->getTermCount(tempTerm) > 0)
        {
            documentCount++;
        }
    }

    if(documentCount > 0)
        return (double)std::log((double)(_documentCollection.getCollection().size())/(double)documentCount);
    else
        return 0;
}

//------------------------------
//  PRIVATE FUNCTIONS - helpers
//------------------------------

/*/**
 * @brief Agent::countWords
 * @param str
 * @return
 *
 *  http://stackoverflow.com/questions/3672234/c-function-to-count-all-the-words-in-a-string
 */
/*int Agent::countWords(const char *str)
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
}*/

/**
 * @brief Agent::countTermWords
 * @param text
 * @param term
 * @return
 */
/*int Agent::countTermWords(const std::string &text, const std::string &term)
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
}*/

/**
 * @brief Agent::findClosestCluster
 * @param clusterCenter
 * @param data
 * @return
 *
 *  Finds the closest centroid cluster for the given data set.
 */
int Agent::findClosestCluster(const std::vector<Centroid*> clusterCenter, const Data* data)
{
    double similarity[clusterCenter.size()];

    for(int i = 0; i < clusterCenter.size(); i++)
    {
        similarity[i] = calcCosineSimilarity(clusterCenter[i]->getDocuments()[0]->getVectorSpace(), data->getVectorSpace());
    }

    int index = 0;
    double maxVal = similarity[0];
    for(int i = 0; i < clusterCenter.size(); i++)
    {
        if(similarity[i] > maxVal)
        {
            maxVal = similarity[i];
            index = i;
        }
    }
    return index;
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

/**
 * @brief Agent::checkStopCrit
 * @param prevCenterSet
 * @param newCenterSet
 * @return
 *
 *  Checks if the stopping criteria has been reached
 */
bool Agent::checkStopCrit(std::vector<Centroid *> &prevCenterSet, std::vector<Centroid *> &newCenterSet)
{
    _globalCounter++;
    _counter = _globalCounter;

    if(_globalCounter > 11000)
    {
        return true;
    }
    else
    {
        int changeIndex[newCenterSet.size()];
        int index = 0;
        do
        {
            int count = 0;
            if(newCenterSet[index]->getDocuments().size() == 0 && prevCenterSet[index]->getDocuments().size() == 0)
            {
                index++;
            }
            else if(newCenterSet[index]->getDocuments().size() != 0 && prevCenterSet[index]->getDocuments().size() != 0)
            {
                for(int i = 0; i < newCenterSet[index]->getDocuments()[0]->getVectorSpace().size(); i++)
                {
                    if(newCenterSet[index]->getDocuments()[0]->getVectorSpace()[i] == prevCenterSet[index]->getDocuments()[0]->getVectorSpace()[i])
                    {
                        count++;
                    }
                }

                if(count == newCenterSet[index]->getDocuments()[0]->getVectorSpace().size())
                {
                    changeIndex[index] = 0;
                }
                else
                {
                    changeIndex[index] = 1;
                }

                index++;
            }
            else
            {
                index++;
                continue;
            }
        }
        while(index < newCenterSet.size());

        for(int i = 0; i < newCenterSet.size(); i++)
        {
            if(changeIndex[i] != 0)
                return false;
        }
        return true;
    }
}

std::vector<Centroid *> Agent::calcMeanPoints(std::vector<Centroid *> &clusterCenter)
{
    for(int i = 0; i < clusterCenter.size(); i++)
    {
        if(clusterCenter[i]->getDocuments().size() > 0)
        {
            for(int j = 0; j < clusterCenter[i]->getDocuments()[0]->getVectorSpace().size(); j++)
            {
                double total = 0.0;

                for(int k = 0; k < clusterCenter[i]->getDocuments().size(); k++)
                {
                    total += clusterCenter[i]->getDocuments()[k]->getVectorSpace()[j];
                }
                clusterCenter[i]->getDocuments()[0]->setVectorSpaceAt(total / clusterCenter[i]->getDocuments().size(), j);
            }
        }
    }
    return clusterCenter;
}
