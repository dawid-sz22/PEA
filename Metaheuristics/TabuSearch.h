#ifndef UNTITLED_TABUSEARCH_H
#define UNTITLED_TABUSEARCH_H
#include <vector>
#include "../Graphs/AdjacencyMatrix.h"
#include "../Tools/TabuElement.h"

class TabuSearch {
    AdjacencyMatrix* matrix;
    std::vector<int> shortestPath;
    int shortestPathValue;
    double timeStop;
    int term;
    double timeWhenBest;
    int iterationsWithNoChangeMAX;
    int iterationsWithNoChange;
    int neighborhoodType; ///1 -  SWAP ; 2 - INSERT ; 3 - INVERT
public:
    TabuSearch(AdjacencyMatrix* matrix, double time, int iterationsWithNoChangeMAX, int term, int neighborhoodType);
    void greedyRoute();
    void randomRoute(std::vector<int> &source);
    void start();
    int countPath(int tempValue, int I, int J, std::vector<int> &source);
    int countPath(std::vector<int> &source);
    void printResults();
    int getPathValue() const;
    std::vector<int> getShortestPath();
    int getTime();
    void insert(std::vector<int>& v, int oldIndex, int newIndex);
};


#endif //UNTITLED_TABUSEARCH_H
