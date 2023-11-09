#include <cstdint>
#include "BruteForce.h"
BruteForce::BruteForce(AdjacencyMatrix* matrix) : matrix(matrix), heap(new int [matrix->getNodesCount()]),
endHeap(new int[matrix->getNodesCount()]), visitedNodes(new bool[matrix->getNodesCount()]), heapSize(0),
pathWeightEnd(INT32_MAX), pathWeightHelp(0)
{}

BruteForce::~BruteForce() {
    delete[] heap;
    delete[] visitedNodes;
}

int* BruteForce::main() {

    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        visitedNodes[i] = false;
        endHeap[i] = -1;
    }


    /// ZACZYNAMY POSZUKIWANIA OD WIERZCOHŁKA POCZĄTKOWEGO (def. 0), i przeszukujemy wszystkie możliwe rozwiązania rekurencyjnie
    nextNodeBF(matrix->getStartNode());

    return endHeap;                             //zwracamy końcową optymalna ścieżkę
}

void BruteForce::nextNodeBF(int node) {
    heap[heapSize++] = node;                    //zapisujemy nowy wierzchołek na stosie

    if(heapSize < matrix->getNodesCount())                   //jeśli rozmiar stosu, jest mniejszy od ilości wierzchołków -->
    {                                           //to oznacza to,że nie znaleziono jeszcze całkowitej ścieżki
        visitedNodes[node] = true;              //oznaczamy jako odwiedzony
        for (int i = 0; i < matrix->getNodesCount(); ++i) {  //przeglądanie wszystkich sąsiadów, aby znaleźć wierzchołek, który jeszcze nie jest połączony
            if (!visitedNodes[i])
            {
                pathWeightHelp += matrix->getWsk()[node][i]; //dodaj koszt do tymczasowej drogi
                nextNodeBF(i);    //szukaj zatem kolejnego wierzchołka
                pathWeightHelp -= matrix->getWsk()[node][i]; //zakończono rozważanie wierzchołka i, zatem usuń wagę krawędzi która łączy node z i
            }
        }
        visitedNodes[node] = false;             //brak nowych kandydatów na ścieżkę --> odznacz wierzhołek
        heapSize--;                             //zmiejsz stos o 1, z powodu braku nowych rozwiązań z tego wierzchołka
    }
    else                                        //rozmiar stosu jest równy ilości wierzchołków
    {                                           //--> dotarto do końca możliwych rozwiązań w danej gałęzi
        pathWeightHelp += matrix->getWsk()[node][matrix->getStartNode()];
        if (pathWeightHelp < pathWeightEnd)      //jeśli aktualna suma jest mniejsza od aktualnie optymalnego rozwiązania
        {                                        //---> zamień dane
            pathWeightEnd = pathWeightHelp;
            for (int i = 0; i < heapSize; ++i) {
                endHeap[i] = heap[i];
            }
        }
        pathWeightHelp -= matrix->getWsk()[node][matrix->getStartNode()]; //policzono cały koszt ścieżki, która już nie ma dalszego ciągu, zatem usuń ostatnią wage
        heapSize--;                             //zmniejszamy rozmiar stosu (usuwamy tym samym ostatni wierzchołek)
    }
}

