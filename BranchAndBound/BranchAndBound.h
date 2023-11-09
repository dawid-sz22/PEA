#ifndef UNTITLED_BRANCHANDBOUND_H
#define UNTITLED_BRANCHANDBOUND_H


#include "../Graphs/AdjacencyMatrix.h"
#include "../Tools/NodeBB.h"
#include <list>

class BranchAndBound {
    AdjacencyMatrix* matrix;
public:
    BranchAndBound(AdjacencyMatrix* matrix);

    std::list<NodeBB*> main();
    void countMatrix(NodeBB* node, NodeBB* father);
    void blockMatrix(NodeBB *node, NodeBB* father);
};


#endif //UNTITLED_BRANCHANDBOUND_H
