#ifndef AGENT_H
#define AGENT_H

#include <string>
#include <vector>

#include "data.h"
#include "centroid.h"

class Agent
{
public:
    Agent();

    void kMeanCluster();

    double calcEuclDist(Data *data, Centroid *centroid);







private:
    std::vector<Data> _dataCollection;


    double findTFIDF(Data *doc, std::string &term);
    double findTermFrequency(Data *doc, std::string &term);
    double findInverseDocumentFrequency(const std::string &term);

    int countWords(const char* str);
    int countTermWords(const std::string &text, const std::string &term);

};

#endif // AGENT_H
