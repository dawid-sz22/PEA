#ifndef UNTITLED_BRUTEFORCE_H
#define UNTITLED_BRUTEFORCE_H


#include "../Graphs/AdjacencyMatrix.h"

class BruteForce {
    AdjacencyMatrix* matrix;
    int* heap;              //stworzenie stosu, który będzie zawierać kolejne wierzchołki trasy komiwojążera
    int* endHeap;           //końcowa ścieżka
    bool* visitedNodes;     //tablica, która przechowuje odwiedzone już wierzchołki
    int heapSize;           //aktualny rozmiar stosu
    int pathWeightEnd;      //koszt wyliczonej końcowej drogi
    int pathWeightHelp;     //koszt wyliczonej tymczasowej drogi
public:
    BruteForce(AdjacencyMatrix* matrix);
    ~BruteForce();
    int* main();
    void nextNodeBF(int node);

};


#endif //UNTITLED_BRUTEFORCE_H
