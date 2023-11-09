#ifndef SDIZO2_ADJACENCYMATRIX_H
#define SDIZO2_ADJACENCYMATRIX_H

class AdjacencyMatrix {
    int** wsk;
    int nodesCount;
    int startNode;

public:
    ~AdjacencyMatrix();
    AdjacencyMatrix();
    AdjacencyMatrix(int nodes, int start, bool random);

    void printMatrix();

    int* bruteForce();
    void nextNodeBF(int node,int* heap,int* heapEnd, int& heapSize, bool* visitedNodes,int& pathWeightHelp, int& pathWeight);

    int** getWsk();
    int getNodesCount();
    int getStartNode();
};


#endif //SDIZO2_ADJACENCYMATRIX_H
