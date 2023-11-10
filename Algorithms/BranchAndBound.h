#ifndef UNTITLED_BRANCHANDBOUND_H
#define UNTITLED_BRANCHANDBOUND_H


#include "../Graphs/AdjacencyMatrix.h"
#include "../Tools/NodeBB.h"
#include <list>
#include <vector>
#include <atomic>
#include <queue>

//stworzenie struktury do implemenetacji kolejki priorytetowej, aby móc sortować obiekty po zmiennych "lowerBound"
struct compareLowerBound {
    bool operator()(NodeBB* const & n1, NodeBB* const & n2)
    {
        return n1->lowerBound > n2->lowerBound;
    }
};

class BranchAndBound {
    AdjacencyMatrix* matrix;
    std::priority_queue<NodeBB*, std::vector<NodeBB*>,compareLowerBound> queue;
    //Lista, która zawiera wierzchołki rozszerzone, które należy jeszcze usunąc
    //(lista zawiera również w sobie wierzchołki, które są zawarte w ścieżce, dlatego też zwracamy tą listę
    //jako wynik funkcji
    std::list<NodeBB*> listToDelete;
public:
    BranchAndBound(AdjacencyMatrix* matrix);

    std::list<NodeBB*> main();
    std::list<NodeBB*> main(std::atomic<bool> &stopFlag);
    void countMatrix(NodeBB* node, NodeBB* father);
    void blockMatrix(NodeBB *node, NodeBB* father);
    void clear();

};


#endif //UNTITLED_BRANCHANDBOUND_H
