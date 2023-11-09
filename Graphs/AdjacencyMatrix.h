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


    int** getWsk();
    int getNodesCount();
    int getStartNode();

};


#endif //SDIZO2_ADJACENCYMATRIX_H
