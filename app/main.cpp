#include <iostream>

#include "agent.h"
#include "document.h"
#include "documentcollection.h"

using namespace std;

int main()
{
    Agent agent;
    DocumentCollection collection;
    collection.addDocument(new Document("../testdoc.txt"));
    collection.addDocument(new Document("../testdoc2.txt"));


    agent.processDocuments(collection);



    return 0;
}

