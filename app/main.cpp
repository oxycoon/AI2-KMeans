#include <iostream>

#include "agent.h"
#include "centroid.h"
#include "document.h"
#include "documentcollection.h"
#include "filter.h"

#include "filters/masseffect.h"
#include "filters/callofduty.h"
#include "filters/fifa.h"
#include "filters/worldofwarcraft.h"

using namespace std;

int main()
{
    Agent agent;
    DocumentCollection collection;
    collection.addDocument(new Document("../res/masseffect1.txt"));
    collection.addDocument(new Document("../res/masseffect2.txt"));
    collection.addDocument(new Document("../res/masseffect3.txt"));
    collection.addDocument(new Document("../res/masseffect4.txt"));
    collection.addDocument(new Document("../res/masseffect5.txt"));
    collection.addDocument(new Document("../res/masseffect6.txt"));
    collection.addDocument(new Document("../res/masseffect7.txt"));
    collection.addDocument(new Document("../res/fifa1.txt"));
    collection.addDocument(new Document("../res/fifa2.txt"));
    collection.addDocument(new Document("../res/fifa3.txt"));
    collection.addDocument(new Document("../res/fifa4.txt"));
    collection.addDocument(new Document("../res/fifa5.txt"));
    collection.addDocument(new Document("../res/fifa6.txt"));
    collection.addDocument(new Document("../res/fifa7.txt"));
    collection.addDocument(new Document("../res/wow1.txt"));
    collection.addDocument(new Document("../res/wow2.txt"));
    collection.addDocument(new Document("../res/wow3.txt"));
    collection.addDocument(new Document("../res/wow4.txt"));
    collection.addDocument(new Document("../res/wow5.txt"));
    collection.addDocument(new Document("../res/wow6.txt"));
    collection.addDocument(new Document("../res/wow7.txt"));
    collection.addDocument(new Document("../res/cod1.txt"));
    collection.addDocument(new Document("../res/cod2.txt"));
    collection.addDocument(new Document("../res/cod3.txt"));
    collection.addDocument(new Document("../res/cod4.txt"));
    collection.addDocument(new Document("../res/cod5.txt"));
    collection.addDocument(new Document("../res/cod6.txt"));
    collection.addDocument(new Document("../res/cod7.txt"));

    std::vector<Filter*> filters;
    filters.push_back(new MassEffect());
    filters.push_back(new WorldOfWarcraft());
    filters.push_back(new CallOfDuty());
    filters.push_back(new Fifa());

    std::vector<Data*> dataSet;
    dataSet = agent.processDocuments(collection, filters);

    std::vector<Data*> seeds;
    seeds.push_back(dataSet[2]);
    seeds.push_back(dataSet[7]);
    seeds.push_back(dataSet[14]);
    seeds.push_back(dataSet[21]);

    std::vector<Centroid*> resultSet;
    int counter = 0;
    resultSet = agent.prepareDocumentCluster(dataSet, seeds, counter);

    for(int i = 0; i < resultSet.size(); i++)
    {
        std::cout << "Set #" << i+1 << std::endl;
        resultSet[i]->printGroup();
    }


    return 0;
}

