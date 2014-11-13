#ifndef AGENT_H
#define AGENT_H

#include <string>
#include <vector>

#include "data.h"
#include "centroid.h"
#include "documentcollection.h"

class Document;
class Filter;

class Agent
{
public:
    Agent();
    ~Agent();

    std::vector<Centroid *> prepareDocumentCluster(int k, std::vector<Data*> &collection, int &counter);
    std::vector<Data *> processDocuments(DocumentCollection &collection);
    std::vector<Data *> processDocuments(DocumentCollection &collection, const std::vector<Filter*> &filter);

private:
    DocumentCollection _documentCollection;
    std::vector<Data*> _dataCollection;
    std::vector<std::string> _distinctTerms;
    std::vector<std::string> _nonWordList;
    int _globalCounter;
    int _counter;

    //Initializers
    void initNonWords();
    void initClusterCenter(std::vector<Centroid*> &centroids, int size);

    //Vector space functions
    double findTFIDF(Document *doc, std::string &term);
    double findTermFrequency(Document *doc, std::string &term);
    double findInverseDocumentFrequency(const std::string &term);

    //help functions
    int countWords(const char* str);
    int countTermWords(const std::string &text, const std::string &term);
    int findClosestCluster(const std::vector<Centroid*> clusterCenter, const Data* data);

    double calcDotProduct(const std::vector<double> &vecA, const std::vector<double> &vecB);
    double calcMagnitude(const std::vector<double> &vector);
    double calcEuclDist(const std::vector<double> &vecA, const std::vector<double> &vecB);
    double calcCosineSimilarity(const std::vector<double> &vecA, const std::vector<double> &vecB);

    void generateRandomNumbers(std::vector<int> &set, const int k, const int docs);

    bool checkForNonWord(const char* word);
    bool checkStopCrit(std::vector<Centroid*> &prevCenterSet, std::vector<Centroid*> &newCenterSet);
    bool contains(const std::vector<int> &set, const int item);

    std::vector<Centroid*> calcMeanPoints(std::vector<Centroid*> &clusterCenter);

    //functions to clear the designated vectors of items
    void clearVector(std::vector<Data*> &vector);
    void clearVector(std::vector<Centroid*> &vector);
};

#endif // AGENT_H
