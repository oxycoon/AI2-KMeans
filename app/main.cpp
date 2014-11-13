#include <iostream>

#include "agent.h"
#include "centroid.h"
#include "document.h"
#include "documentcollection.h"
#include "filter.h"

#include "filters/masseffect.h"

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



    std::vector<Filter*> filters;
    filters.push_back(new MassEffect());

    agent.processDocuments(collection, filters);
    //std::cout << agent.prepareDocumentCluster()



    return 0;
}

