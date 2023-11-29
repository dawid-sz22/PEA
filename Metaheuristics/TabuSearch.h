#ifndef UNTITLED_TABUSEARCH_H
#define UNTITLED_TABUSEARCH_H
#include <vector>
#include "../Graphs/AdjacencyMatrix.h"

class TabuSearch {
    AdjacencyMatrix* matrix;
    int* shortestPath;
    int shortestPathValue;
    int tabuListSize;
    double timeStop;
    int tabuListMAXSize;
public:
    TabuSearch(AdjacencyMatrix* matrix, double time);
    void greedyRoute();
    int* start();
    int countPath(int tempValue, int swapFrom, int swapTo, int* source);
    int countPath(int* source);
    void printResults();
};


#endif //UNTITLED_TABUSEARCH_H
