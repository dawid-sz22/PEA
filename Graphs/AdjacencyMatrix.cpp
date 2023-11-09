#include "AdjacencyMatrix.h"
#include "../Tools/Array.h"
#include <iostream>
#include <iomanip>

using namespace std;

AdjacencyMatrix::AdjacencyMatrix():nodesCount(-1),wsk(nullptr),startNode(-1)
{}
AdjacencyMatrix::~AdjacencyMatrix()
{
    for (int i = 0; i < nodesCount; ++i) {
        delete wsk[i];
    }
    delete[] wsk;
}
AdjacencyMatrix::AdjacencyMatrix(int nodes,int start, bool random)
{
    nodesCount = nodes;
    startNode = start;
    wsk = new int*[nodesCount];

    if (random)     //tworzenie randomowego grafu (liczby od 0 do 500)
    {
        Generator generator;

        for (int i = 0; i < nodesCount; ++i) {
            wsk[i] = new int[nodesCount];
            for (int j = 0; j < nodesCount; ++j) {
                if (i!=j)
                    wsk[i][j] = generator.getNumber();
                else
                    wsk[i][j] = -1;
            }
        }
    } else
    {
        //wypełnij macierz zerami w przeciwnym wypadku
        for (int i = 0; i < nodesCount; ++i) {
            wsk[i] = new int[nodesCount];
            for (int j = 0; j < nodesCount; ++j) {
                wsk[i][j] = 0;
            }
        }
    }

}

int* AdjacencyMatrix::bruteForce() {
    int* heap =  new int[nodesCount];           //stworzenie stosu, który będzie zawierać kolejne wierzchołki trasy komiwojążera
    int* endHeap = new int[nodesCount];         //końcowa ścieżka
    bool* visitedNodes = new bool[nodesCount];  //tablica, która przechowuje odwiedzone już wierzchołki
    for (int i = 0; i < nodesCount; ++i) {
        visitedNodes[i] = false;
        endHeap[i] = -1;
    }
    int heapSize = 0;                           //aktualny rozmiar stosu
    int pathWeightEnd = INT32_MAX;              //koszt wyliczonej końcowej drogi
    int pathWeightHelp = 0;                     //koszt wyliczonej tymczasowej drogi

    /// ZACZYNAMY POSZUKIWANIA OD WIERZCOHŁKA POCZĄTKOWEGO (def. 0), i przeszukujemy wszystkie możliwe rozwiązania rekurencyjnie
    nextNodeBF(startNode, heap, endHeap, heapSize,visitedNodes,pathWeightHelp,pathWeightEnd);

    return endHeap;                             //zwracamy końcową optymalna ścieżkę
}

void AdjacencyMatrix::nextNodeBF(int node, int* heap, int* endHeap, int& heapSize, bool* visitedNodes,int& pathWeightHelp, int& pathWeightEnd) {
    heap[heapSize++] = node;                    //zapisujemy nowy wierzchołek na stosie

    if(heapSize < nodesCount)                   //jeśli rozmiar stosu, jest mniejszy od ilości wierzchołków -->
    {                                           //to oznacza to,że nie znaleziono jeszcze całkowitej ścieżki
        visitedNodes[node] = true;              //oznaczamy jako odwiedzony
        for (int i = 0; i < nodesCount; ++i) {  //przeglądanie wszystkich sąsiadów, aby znaleźć wierzchołek, który jeszcze nie jest połączony
            if (!visitedNodes[i])
            {
                pathWeightHelp += wsk[node][i]; //dodaj koszt do tymczasowej drogi
                nextNodeBF(i,heap,endHeap,heapSize,visitedNodes,pathWeightHelp,pathWeightEnd);    //szukaj zatem kolejnego wierzchołka
                pathWeightHelp -= wsk[node][i]; //zakończono rozważanie wierzchołka i, zatem usuń wagę krawędzi która łączy node z i
            }
        }
        visitedNodes[node] = false;             //brak nowych kandydatów na ścieżkę --> odznacz wierzhołek
        heapSize--;                             //zmiejsz stos o 1, z powodu braku nowych rozwiązań z tego wierzchołka
    }
    else                                        //rozmiar stosu jest równy ilości wierzchołków
    {                                           //--> dotarto do końca możliwych rozwiązań w danej gałęzi
        pathWeightHelp += wsk[node][startNode];
        if (pathWeightHelp < pathWeightEnd)      //jeśli aktualna suma jest mniejsza od aktualnie optymalnego rozwiązania
        {                                        //---> zamień dane
            pathWeightEnd = pathWeightHelp;
            for (int i = 0; i < heapSize; ++i) {
               endHeap[i] = heap[i];
            }
        }
        pathWeightHelp -= wsk[node][startNode]; //policzono cały koszt ścieżki, która już nie ma dalszego ciągu, zatem usuń ostatnią wage
        heapSize--;                             //zmniejszamy rozmiar stosu (usuwamy tym samym ostatni wierzchołek)
    }
}

int **AdjacencyMatrix::getWsk() {
    return wsk;
}

int AdjacencyMatrix::getNodesCount() {
    return nodesCount;
}

int AdjacencyMatrix::getStartNode() {
    return startNode;
}

void AdjacencyMatrix::printMatrix() {
    cout << "MACIERZ SASIEDZTWA" << endl;
    cout << "    ";
    for(int i = 0; i < nodesCount; i++ )
    {
        cout << setw ( 3 ) << i << "|";
    }
    cout << endl;
    cout << setw(4*nodesCount+4) << setfill('-')<< '-' <<endl;
    cout<<setfill(' ');

    for(int i = 0; i < nodesCount; i++ )
    {
        cout << setw ( 3 ) << i << '|';
        for(int j = 0; j < nodesCount; j++ )
        {
            if (wsk[i][j] != -1)
                cout << setw (3) << wsk[i][j];
            else
                cout << setw (3) << '-';

            cout<<' ';
        }
        cout << endl;
    }
}
