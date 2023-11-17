#include "BranchAndBound.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
BranchAndBound::BranchAndBound(AdjacencyMatrix *matrix) : matrix(matrix)
{}
list<NodeBB *> BranchAndBound::mainStop() {
    //stworzenie pomocniczego wierzchołka, który będzie imitował ojca korzenia
    NodeBB* root = new NodeBB(matrix->getStartNode(),0, matrix->getNodesCount(), nullptr);

    //inicjalizacja macierzy korzenia
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        for (int j = 0; j < matrix->getNodesCount(); ++j) {
            if (i==j)
                root->table[i][j] = INT32_MAX;              //na przekątnych nieskończoności zamiast -1
            else
                root->table[i][j] = matrix->getWsk()[i][j];
        }
    }

    ///Zaczynamy od obliczenia macierzy korzenia i jego LB (lowerBound)
    countMatrix(root, nullptr);

    findUpperBound();

    queue.push(root);

    NodeBB* newNode;
    NodeBB* nodeFromQueue;

    while (queue.top()->level != matrix->getNodesCount()-1) {
        nodeFromQueue = queue.top();
        queue.pop();    //usuwamy wierzchołek z kolejki
        listToDelete.push_back(nodeFromQueue);
        for (int i = 0; i < matrix->getNodesCount(); ++i) {
            if (queue.size() > 3318784)
            {
                cout <<"ROZMIAR: " << queue.size() << endl;
                return {};
            }

            //szukamy wolnych dróg z wylosowanego wierzchołka
            if (nodeFromQueue->table[nodeFromQueue->numberOfNode][i] != INT32_MAX) {
                newNode = new NodeBB(i, nodeFromQueue->level + 1, matrix->getNodesCount(), nodeFromQueue);
                blockMatrix(newNode, nodeFromQueue);
                countMatrix(newNode, nodeFromQueue);
                if (newNode->lowerBound > upperBound) {
                    delete newNode;
                    continue;
                } else {
                    //jeśli doszliśmy podczas sprawdzania potomków do liścia i jego LB jest mniej niż UP, zaaktualizuj UP
                    //oraz usuń wierzchołki, które mają LB > nowego UP
                    if((newNode->level == matrix->getNodesCount()-1) && newNode->lowerBound < upperBound)
                    {
                        upperBound = newNode->lowerBound;
                        NodeBB* nodeCheck;
                        std::priority_queue<NodeBB*, std::vector<NodeBB*>,compareLowerBound> newQueue;
                        while(!queue.empty())
                        {
                            nodeCheck = queue.top();
                            queue.pop();
                            if (nodeCheck->lowerBound > upperBound)
                            {
                                delete nodeCheck;
                            } else
                            {
                                newQueue.push(nodeCheck);
                            }
                        }
                        queue = newQueue;
                    }
                    queue.push(newNode);    //dodajemy do kolejki nowy wierzchołek
                }
            }
        }
    }
    ///Znaleziono liść, który jest jednocześnie lowerBound
    NodeBB* nodeEnd = queue.top();
    queue.pop();

    listToDelete.push_back(nodeEnd);



    return listToDelete;
}


list<NodeBB*> BranchAndBound::main() {
    //stworzenie pomocniczego wierzchołka, który będzie imitował ojca korzenia
    NodeBB* root = new NodeBB(matrix->getStartNode(),0, matrix->getNodesCount(), nullptr);

    //inicjalizacja macierzy korzenia
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        for (int j = 0; j < matrix->getNodesCount(); ++j) {
            if (i==j)
                root->table[i][j] = INT32_MAX;              //na przekątnych nieskończoności zamiast -1
            else
                root->table[i][j] = matrix->getWsk()[i][j];
        }
    }

    ///Zaczynamy od obliczenia macierzy korzenia i jego LB (lowerBound)
    countMatrix(root, nullptr);

    findUpperBound();

    queue.push(root);

    NodeBB* newNode;
    NodeBB* nodeFromQueue;

    while (queue.top()->level != matrix->getNodesCount()-1) {
        nodeFromQueue = queue.top();
        queue.pop();    //usuwamy wierzchołek z kolejki
        listToDelete.push_back(nodeFromQueue);
        for (int i = 0; i < matrix->getNodesCount(); ++i) {

            //szukamy wolnych dróg z wylosowanego wierzchołka
            if (nodeFromQueue->table[nodeFromQueue->numberOfNode][i] != INT32_MAX) {
                newNode = new NodeBB(i, nodeFromQueue->level + 1, matrix->getNodesCount(), nodeFromQueue);
                blockMatrix(newNode, nodeFromQueue);
                countMatrix(newNode, nodeFromQueue);
                if (newNode->lowerBound > upperBound) {
                    delete newNode;
                    continue;
                } else {
                    //jeśli doszliśmy podczas sprawdzania potomków do liścia i jego LB jest mniej niż UP, zaaktualizuj UP
                    //oraz usuń wierzchołki, które mają LB > nowego UP
                    if((newNode->level == matrix->getNodesCount()-1) && newNode->lowerBound < upperBound)
                    {
                        upperBound = newNode->lowerBound;
                        NodeBB* nodeCheck;
                        std::priority_queue<NodeBB*, std::vector<NodeBB*>,compareLowerBound> newQueue;
                        while(!queue.empty())
                        {
                            nodeCheck = queue.top();
                            queue.pop();
                            if (nodeCheck->lowerBound > upperBound)
                            {
                                delete nodeCheck;
                            } else
                            {
                                newQueue.push(nodeCheck);
                            }
                        }
                        queue = newQueue;
                    }
                    queue.push(newNode);    //dodajemy do kolejki nowy wierzchołek
                }
            }
        }
    }
    ///Znaleziono liść, który jest jednocześnie lowerBound
    NodeBB* nodeEnd = queue.top();
    queue.pop();
    listToDelete.push_back(nodeEnd);

    return listToDelete;
}


void BranchAndBound::countMatrix(NodeBB* node, NodeBB* father) {
    int *tableCountRow = new int [matrix->getNodesCount()];
    int *tableCountColumn = new int [matrix->getNodesCount()];

    ///Przeszukujemy wszystkie wiersze w poszukiwaniu stałych do usunięcia z macierzy
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        tableCountRow[i] = INT32_MAX;                   //przypisujemy nieskończoność, aby znaleść minimalną liczbę w wierszu
        for (int j = 0; j < matrix->getNodesCount(); ++j) {
            if (node->table[i][j] < tableCountRow[i])
                tableCountRow[i] = node->table[i][j];     //szukanie liczby najmniejszej w wierszu
        }
        if (tableCountRow[i] != INT32_MAX && tableCountRow[i] != 0) {
            for (int j = 0; j < matrix->getNodesCount(); ++j) {      //jeśli nie jest to nieskończoność i 0, to znaleziono stałą to odjęcia
                if (node->table[i][j] != INT32_MAX)
                    node->table[i][j] -= tableCountRow[i];    //w wierszu usuwamy najmniejszą liczbę znalezioną w wierszu
            }
        } else
            tableCountRow[i] = 0;                        //jeśli po przeszukaniu, znaleziono same nieskończoności to zapisz 0
    }

    ///Przeszukujemy wszystkie kolumny w poszukiwaniu stałych do usunięcia z macierzy
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        tableCountColumn[i] = INT32_MAX;                   //przypisujemy nieskończoność, aby znaleść minimalną liczbę w wierszu
        for (int j = 0; j < matrix->getNodesCount(); ++j) {
            if (node->table[j][i] < tableCountColumn[i])
                tableCountColumn[i] = node->table[j][i];     //szukanie liczby najmniejszej w wierszu
        }
        if (tableCountColumn[i] != INT32_MAX && tableCountColumn[i] != 0) {
            for (int j = 0;
                 j < matrix->getNodesCount(); ++j) {      //jeśli nie jest to nieskończoność i 0, to znaleziono stałą to odjęcia
                if (node->table[j][i] != INT32_MAX)
                    node->table[j][i] -= tableCountColumn[i];    //w wierszu usuwamy najmniejszą liczbę znalezioną w wierszu
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
        node->lowerBound += father->table[father->numberOfNode][node->numberOfNode];
    }

    delete[] tableCountColumn;
    delete[] tableCountRow;
}

void BranchAndBound::blockMatrix(NodeBB *node, NodeBB* father) {
    ///BLOKOWANIE WIERSZA/KOLUMNY W MACIERZY
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        node->table[father->numberOfNode][i] = INT32_MAX;   //Blokowanie wiersza
        node->table[i][node->numberOfNode] = INT32_MAX;           //Blokowanie kolumny
    }
    node->table[node->numberOfNode][matrix->getStartNode()] = INT32_MAX;  //Blokowanie powrotu do wierzchołka początkowego

}

void BranchAndBound::clear() {
    NodeBB* nodeFromQueue;
    while (!queue.empty())
    {
        //usuwanie wierzchołków z pamięci, z kolejki
        nodeFromQueue = queue.top();
        queue.pop();
        delete nodeFromQueue;
    }

    for (NodeBB* node: listToDelete) {
        delete node;
    }
}

void BranchAndBound::findUpperBound() {
    std::priority_queue<NodeBB*, std::vector<NodeBB*>,compareLowerBound> queueHelp;
    //kopia
    NodeBB* rootNode = new NodeBB(matrix->getStartNode(),0, matrix->getNodesCount(), nullptr);

    //inicjalizacja macierzy korzenia
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        for (int j = 0; j < matrix->getNodesCount(); ++j) {
            if (i==j)
                rootNode->table[i][j] = INT32_MAX;              //na przekątnych nieskończoności zamiast -1
            else
                rootNode->table[i][j] = matrix->getWsk()[i][j];
        }
    }

    ///Zaczynamy od obliczenia macierzy korzenia i jego LB (lowerBound)
    countMatrix(rootNode, nullptr);

    queueHelp.push(rootNode);


    NodeBB* helpNode;
    NodeBB* newNode;
    NodeBB* nodeFromQueue;

    while (queueHelp.top()->level != matrix->getNodesCount()-1) {
        nodeFromQueue = queueHelp.top();
        queueHelp.pop();    //usuwamy wierzchołek z kolejki
        while (!queueHelp.empty())
        {
            //usuwanie wierzchołków z pamięci, z kolejki
            helpNode = queueHelp.top();
            queueHelp.pop();
            delete helpNode;
        }

        for (int i = 0; i < matrix->getNodesCount(); ++i) {

            //szukamy wolnych dróg z wylosowanego wierzchołka
            if (nodeFromQueue->table[nodeFromQueue->numberOfNode][i] != INT32_MAX) {
                newNode = new NodeBB(i, nodeFromQueue->level + 1, matrix->getNodesCount(), nodeFromQueue);
                blockMatrix(newNode, nodeFromQueue);
                countMatrix(newNode, nodeFromQueue);
                queueHelp.push(newNode);
            }
        }
        delete nodeFromQueue;
    }
    upperBound = queueHelp.top()->lowerBound;
    while (!queueHelp.empty())
    {
        //usuwanie wierzchołków z pamięci, z kolejki
        helpNode = queueHelp.top();
        queueHelp.pop();
        delete helpNode;
    }

}



