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
