#ifndef UNTITLED_TABUSEARCH_H
#define UNTITLED_TABUSEARCH_H
#include <vector>
#include "../Graphs/AdjacencyMatrix.h"
#include "../Tools/TabuElement.h"

class TabuSearch {
    AdjacencyMatrix* matrix;
    std::vector<int> shortestPath;
    std::vector<std::vector<double>> shortestPathChanging;  //przchowuje zmiany ścieżki na lepsze (cost,time)
    int shortestPathValue;
    int greedyPathValue;
    double timeStop;
    int term;
    double timeWhenBest;
    int iterationsWithNoChangeMAX;
    int iterationsWithNoChange;
    int neighborhoodType;    ///1 -  SWAP ; 2 - INSERT ; 3 - INVERT
    int aspirationPlus;     //różnica pomiędzy znalezionym rozwiązaniem, a najlepszym, która pozwala na zignorowanie tabu
    int bestKnownResult;    //znane optymalne rozwiązanie, do porównania wyników
public:
    TabuSearch(AdjacencyMatrix* matrix, int bestKnownResult, double time, int iterationsWithNoChangeMAX, double k, int neighborhoodType, int aspirationPlus);
    void greedyRoute();
    void randomRoute(std::vector<int> &source);
    void start();
    int countPath(int tempValue, int I, int J, std::vector<int> &source);
    int countPath(std::vector<int> &source);
    void printResults();
    int getPathValue();
    std::vector<int> getShortestPath();
    int getTime();
    std::vector<std::vector<double>> getPathChanging();
    void insert(std::vector<int>& v, int oldIndex, int newIndex);
};


#endif //UNTITLED_TABUSEARCH_H
