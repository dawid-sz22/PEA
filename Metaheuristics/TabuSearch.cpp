#include <iostream>
#include "TabuSearch.h"
#include "../Tools/Timer.h"
#include "../Tools/Generator.h"

TabuSearch::TabuSearch(AdjacencyMatrix* matrix, double timeStop) : matrix(matrix), timeStop(timeStop)
{}


void TabuSearch::greedyRoute() {

    shortestPath = new int[matrix->getNodesCount() + 1];

    //dodaj na początek wierzchołek startowy
    shortestPath[0] = matrix->getStartNode();

    bool* alreadyVisited = new bool[matrix->getNodesCount()];
    for (int i = 0; i < matrix->getNodesCount(); i++) {
        alreadyVisited[i] = false;
    }
    //wierzchołek startowy oznaczony jako odwiedzony
    alreadyVisited[matrix->getStartNode()] = true;

    //przeszukiwanie zachłanne
    for (int i = 0; i < matrix->getNodesCount(); i++) {
        int min = INT_MAX;
        int chosen = -1;
        for (int j = 0; j < matrix->getNodesCount(); j++) {
            if (matrix->getWsk()[shortestPath[i]][j] < min && !alreadyVisited[j]) {
                min = matrix->getWsk()[shortestPath[i]][j];
                chosen = j;
            }
        }
        alreadyVisited[chosen] = true;
        shortestPath[i+1] = chosen;
    }

    //dodaj na koniec powrót
    shortestPath[matrix->getNodesCount()] = matrix->getStartNode();

    //obliczanie wartości najkrótszej ścieżki
    shortestPathValue = countPath(shortestPath);

    delete[] alreadyVisited;

}


int TabuSearch::countPath(int* source) {
    int helpCount = 0;
    for (int i = 0; i < matrix->getNodesCount(); i++) {
        //zliczanie całej wartości ścieżki. Jeśli dojdziemy do ostatniego wierzchołka w ścieżce, policz powrót
        helpCount += matrix->getWsk()[source[i]][source[i+1]];
    }
    return helpCount;
}

int TabuSearch::countPath(int tempValue, int swapFrom, int swapTo, int* source) {
    int minus, plus;

//    for (int i = 0; i < matrix->getNodesCount() + 1; ++i) {
//        cout << source[i] << " -> ";
//    }
//    cout << endl;
    if (abs(swapFrom - swapTo) > 1) {
        //zmniejsz dotychczasową wartość ścieżki o krawędzie, z którymi uczestniczą zamieniane wierzchołki
        minus = (matrix->getWsk()[source[swapFrom - 1]][source[swapFrom]] +
                      matrix->getWsk()[source[swapFrom]][source[swapFrom + 1]]
                      + matrix->getWsk()[source[swapTo - 1]][source[swapTo]] +
                      matrix->getWsk()[source[swapTo]][source[swapTo + 1]]);

        //powiększ wartość ścieżki o krawędzie, z którymi uczestniczą zamieniane wierzchołki (PO MOŻLIWEJ ZAMIANIE)
        plus = (matrix->getWsk()[source[swapFrom - 1]][source[swapTo]] +
                      matrix->getWsk()[source[swapTo]][source[swapFrom + 1]]
                      + matrix->getWsk()[source[swapTo - 1]][source[swapFrom]] +
                      matrix->getWsk()[source[swapFrom]][source[swapTo + 1]]);
    } else
    {
        //zmniejsz dotychczasową wartość ścieżki o krawędzie, z którymi uczestniczą zamieniane wierzchołki
        minus = (matrix->getWsk()[source[swapFrom - 1]][source[swapFrom]] +
                      matrix->getWsk()[source[swapFrom]][source[swapFrom + 1]] +
                      matrix->getWsk()[source[swapTo]][source[swapTo + 1]]);

        //powiększ wartość ścieżki o krawędzie, z którymi uczestniczą zamieniane wierzchołki (PO MOŻLIWEJ ZAMIANIE)
        plus = (matrix->getWsk()[source[swapFrom - 1]][source[swapTo]] +
                        matrix->getWsk()[source[swapTo]][source[swapFrom]] +
                      matrix->getWsk()[source[swapFrom]][source[swapTo + 1]]);
    }

//    cout << "FROM: "<<swapFrom<< " TO: "<<swapTo <<"  MINUS: " <<minus <<"  PLUS: "<<plus <<endl;
    return tempValue - minus + plus;
}

int* TabuSearch::start() {
    Timer timer;
    Generator generator;
    timer.run();

    greedyRoute();

    //Stworzenie listy Tabu
    int **tabuList = new int *[matrix->getNodesCount()];
    for (int i = 0; i < matrix->getNodesCount(); i++) {
        tabuList[i] = new int[matrix->getNodesCount()];
        for (int j = 0; j < matrix->getNodesCount(); j++) {
            tabuList[i][j] = 0;
        }
    }

    //Przepisanie najlepszej aktualnej ścieżki do tymczasowej ścieżki
    int *currentRoute = new int[matrix->getNodesCount() + 1];
    for (int i = 0; i < matrix->getNodesCount() + 1; ++i) {
        currentRoute[i] = shortestPath[i];
    }

    //rozwiązanie aktualne, dla którego obliczane jest sąsiedztwo
    int currentSolutionValue = shortestPathValue;
    int bestSwapFrom, bestSwapTo, bestSwapValue;
    int diff;
    bool hasBeenFoundBest = false;
    //wykonuje dopóki nie upłynie ustalony czas
    while (timer.read() < timeStop) {
        bestSwapValue = INT_MAX;
        //
        for (int i = 1; i < matrix->getNodesCount(); i++) {
            for (int j = i + 1; j < matrix->getNodesCount(); j++) {
                //różnica pomiędzy wyliczonym rozwiązniem a aktualnym
                diff = countPath(currentSolutionValue,i,j,currentRoute) - currentSolutionValue;

                //wybieranie najlepszego ruchu, który jednocześnie nie jest zabroniony w liście tabu, chyba że (KRYTERIUM ASPIRACJI) ruch, który blokuje
                //lista tabu, polepszy nam aktualne znane rozwiązanie
                if (((diff < bestSwapValue) && tabuList[i][j] == 0) || (currentSolutionValue + diff) < shortestPathValue) {
                    bestSwapValue = diff;
                    bestSwapFrom = i;
                    bestSwapTo = j;
                    hasBeenFoundBest = true;
                }
            }
        }
        //zmniejszenie kadencji w tabu list
        for (int i = 0; i < matrix->getNodesCount(); i++) {
            for (int j = 0; j < matrix->getNodesCount(); j++) {
                if (tabuList[i][j] > 0) {
                    tabuList[i][j]--;
                }
            }
        }

        //sprawdź, czy znaleziono jakieś lepsze rozwiązanie (jeśli tabu zablokuje, wszystkie ruchy --> idź do kolejnej kadencji i nic nie rób)
        if (hasBeenFoundBest)
        {
            //wykorzystując najlepsze rozwiązanie, zamień kolejność oraz nadaj zakaz na ruch
            std::swap(currentRoute[bestSwapFrom], currentRoute[bestSwapTo]);

            //wybieramy losowo kadencje
            int randomTerm = generator.getNumber(20,matrix->getNodesCount()/2);
            tabuList[bestSwapFrom][bestSwapTo] = randomTerm;
            tabuList[bestSwapTo][bestSwapFrom] = randomTerm;
            currentSolutionValue += diff;

            //jeśli znaleziono nowe najlepsze globalne rozwiązanie --> zaaktualizuj
            if (currentSolutionValue < shortestPathValue) {
                std::swap(shortestPath[bestSwapFrom], shortestPath[bestSwapTo]);
                shortestPathValue = currentSolutionValue;
            }
        }
        hasBeenFoundBest = false;

    }

    for (int i = 0; i < matrix->getNodesCount(); i++) {
        delete[] tabuList[i];
    }
    delete[] tabuList;
    delete[] currentRoute;

    return shortestPath;
}

void TabuSearch::printResults() {
    cout << "SCIEZKA\n ";
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        cout << shortestPath[i] << " -> ";
    }
    cout << shortestPath[matrix->getNodesCount()];
    cout << "\nKOSZT: " <<shortestPathValue;

}


