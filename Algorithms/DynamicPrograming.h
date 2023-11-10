#ifndef UNTITLED_DYNAMICPROGRAMING_H
#define UNTITLED_DYNAMICPROGRAMING_H
#include <vector>
#include "../Graphs/AdjacencyMatrix.h"

class DynamicPrograming {
    AdjacencyMatrix* matrix;
    //stała maska, która ma na każdej pozycji 1, np. dla 4 miast: 1111
    int maskAllVisited;
    //końcowy wynik
    int result;
    //tablica o rozmiarach N x 2^N, która przechowuje rozwiązane juz podproblemy
    std::vector<std::vector<int>> subProblems;
    //talblica dodatkowa, która będzie przechowywać nam wierzchołki do ścieżki
    std::vector<std::vector<int>> tablePath;

public:
    DynamicPrograming(AdjacencyMatrix* martrix);
    void main();
    int DPFunction(int mask, int node);
    void printResults();
};


#endif //UNTITLED_DYNAMICPROGRAMING_H
