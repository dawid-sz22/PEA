#include "BranchAndBound.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
BranchAndBound::BranchAndBound(AdjacencyMatrix *matrix) : matrix(matrix)
{}

list<NodeBB*> BranchAndBound::main() {
    //stworzenie struktury do implemenetacji kolejki priorytetowej, aby móc sortować obiekty po zmiennych "lowerBound"
    struct compareLowerBound {
        bool operator()(NodeBB* const & n1, NodeBB* const & n2)
        {
            return n1->lowerBound > n2->lowerBound;
        }
    };
    //stworzenie kolejki priorytetowej do sortowania wierzchołków po zmiennej lowerBound
    auto* queue  = new priority_queue<NodeBB*, vector<NodeBB*>,compareLowerBound>;

    //Lista, która zawiera wierzchołki rozszerzone, które należy jeszcze usunąc
    //(lista zawiera również w sobie wierzchołki, które są zawarte w ścieżce, dlatego też zwracamy tą listę
    //jako wynik funkcji
    list<NodeBB*> listToDelete;

    //stworzenie pomocniczego wierzchołka, który będzie imitował ojca korzenia
    NodeBB* root = new NodeBB(matrix->getStartNode(),0, matrix->getNodesCount(), nullptr);

    //inicjalizacja macierzy korzenia
    root->wsk = new int*[matrix->getNodesCount()];
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        root->wsk[i] = new int [matrix->getNodesCount()];
        for (int j = 0; j < matrix->getNodesCount(); ++j) {
            if (i==j)
                root->wsk[i][j] = INT32_MAX;              //na przekątnych nieskończoności zamiast -1
            else
                root->wsk[i][j] = matrix->getWsk()[i][j];
        }
    }

    ///Zaczynamy od obliczenia macierzy korzenia i jego LB (lowerBound)
    countMatrix(root, nullptr);

    queue->push(root);

    NodeBB* newNode;
    NodeBB* nodeFromQueue;

    while (queue->top()->level != matrix->getNodesCount()-1) {
        nodeFromQueue = queue->top();
        queue->pop();    //usuwamy wierzchołek z kolejki
        for (int i = 0; i < matrix->getNodesCount(); ++i) {
            //szukamy wolnych dróg z wylosowanego wierzchołka
            if (nodeFromQueue->wsk[nodeFromQueue->numberOfNode][i] != INT32_MAX) {
                newNode = new NodeBB(i, nodeFromQueue->level + 1, matrix->getNodesCount(), nodeFromQueue);
                blockMatrix(newNode, nodeFromQueue);
                countMatrix(newNode, nodeFromQueue);
                queue->push(newNode);    //dodajemy do kolejki nowy wierzchołek
            }
        }
        listToDelete.push_back(nodeFromQueue);
    }
    ///Znaleziono liść, który jest jednocześnie lowerBound
    NodeBB* nodeEnd = queue->top();
    queue->pop();

    listToDelete.push_back(nodeEnd);

    while (!queue->empty())
    {
        //usuwanie wierzchołków z pamięci, z kolejki
        nodeFromQueue = queue->top();
        queue->pop();
        delete nodeFromQueue;
    }

    delete queue;
    return listToDelete;
}


void BranchAndBound::countMatrix(NodeBB* node, NodeBB* father) {
    int *tableCountRow = new int[matrix->getNodesCount()];
    int *tableCountColumn = new int[matrix->getNodesCount()];

    ///Przeszukujemy wszystkie wiersze w poszukiwaniu stałych do usunięcia z macierzy
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        tableCountRow[i] = INT32_MAX;                   //przypisujemy nieskończoność, aby znaleść minimalną liczbę w wierszu
        for (int j = 0; j < matrix->getNodesCount(); ++j) {
            if (node->wsk[i][j] < tableCountRow[i])
                tableCountRow[i] = node->wsk[i][j];     //szukanie liczby najmniejszej w wierszu
        }
        if (tableCountRow[i] != INT32_MAX && tableCountRow[i] != 0) {
            for (int j = 0; j < matrix->getNodesCount(); ++j) {      //jeśli nie jest to nieskończoność i 0, to znaleziono stałą to odjęcia
                if (node->wsk[i][j] != INT32_MAX)
                    node->wsk[i][j] -= tableCountRow[i];    //w wierszu usuwamy najmniejszą liczbę znalezioną w wierszu
            }
        } else
            tableCountRow[i] = 0;                        //jeśli po przeszukaniu, znaleziono same nieskończoności to zapisz 0
    }

    ///Przeszukujemy wszystkie kolumny w poszukiwaniu stałych do usunięcia z macierzy
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        tableCountColumn[i] = INT32_MAX;                   //przypisujemy nieskończoność, aby znaleść minimalną liczbę w wierszu
        for (int j = 0; j < matrix->getNodesCount(); ++j) {
            if (node->wsk[j][i] < tableCountColumn[i])
                tableCountColumn[i] = node->wsk[j][i];     //szukanie liczby najmniejszej w wierszu
        }
        if (tableCountColumn[i] != INT32_MAX && tableCountColumn[i] != 0) {
            for (int j = 0;
                 j < matrix->getNodesCount(); ++j) {      //jeśli nie jest to nieskończoność i 0, to znaleziono stałą to odjęcia
                if (node->wsk[j][i] != INT32_MAX)
                    node->wsk[j][i] -= tableCountColumn[i];    //w wierszu usuwamy najmniejszą liczbę znalezioną w wierszu
            }
        } else
            tableCountColumn[i] = 0;                        //jeśli po przeszukaniu, znaleziono same nieskończoności to zapisz 0
    }

    ///Obliczanie lower bound
    //Lower bound = lower bound(father) + costOfPath from Father to Son + reduction
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        node->lowerBound += tableCountRow[i] + tableCountColumn[i];
    }

    if (father != nullptr) {    //ograniczenie dla korzenia

        node->lowerBound += father->lowerBound;
        node->lowerBound += father->wsk[father->numberOfNode][node->numberOfNode];
    }

    delete[] tableCountColumn;
    delete[] tableCountRow;
}

void BranchAndBound::blockMatrix(NodeBB *node, NodeBB* father) {
    ///BLOKOWANIE WIERSZA/KOLUMNY W MACIERZY
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        node->wsk[father->numberOfNode][i] = INT32_MAX;   //Blokowanie wiersza
        node->wsk[i][node->numberOfNode] = INT32_MAX;           //Blokowanie kolumny
    }
    node->wsk[node->numberOfNode][matrix->getStartNode()] = INT32_MAX;  //Blokowanie powrotu do wierzchołka początkowego

}