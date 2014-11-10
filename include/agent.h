#ifndef AGENT_H
#define AGENT_H

#include <string>
#include <vector>
#include <unordered_set>

#include "data.h"
#include "centroid.h"

class Agent
{
public:
    Agent();

    void kMeanCluster();

    double calcEuclDist(std::vector<double> vecA, std::vector<double> vecB);
    double findCosine(std::vector<double> vecA, std::vector<double> vecB);

    std::vector<Data *> prepareDocumentCluster(int k, std::vector<Data*> collection, int counter);

private:
    std::vector<Data*> _dataCollection;
    int _globalCounter;



    double findTFIDF(Data *doc, std::string &term);
    double findTermFrequency(Data *doc, std::string &term);
    double findInverseDocumentFrequency(const std::string &term);

    //help functions
    int countWords(const char* str);
    int countTermWords(const std::string &text, const std::string &term);

    double calcDotProduct(std::vector<double> vecA, std::vector<double> vecB);
    double calcMagnitude(std::vector<double> vector);

    void generateRandomNumbers(std::unordered_set<int> &set, int k, int docs);


};

#endif // AGENT_H
