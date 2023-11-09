#include "NodeBB.h"
NodeBB::~NodeBB() {
    for (int i = 0; i < nodesCount; ++i) {
        delete wsk[i];
    }
    delete [] wsk;

}
NodeBB::NodeBB(int node, int level, int numberOfNodes, NodeBB *father): numberOfNode(node), level(level), lowerBound(0), nodesCount(numberOfNodes), father(father)
{
    if (father!= nullptr)
    {
        wsk = new int*[numberOfNodes];
        for (int i = 0; i < numberOfNodes; ++i) {
            wsk[i] = new int[numberOfNodes];
            for (int j = 0; j < numberOfNodes; ++j) {
                wsk[i][j] = father->wsk[i][j];
            }
        }
    }

}
