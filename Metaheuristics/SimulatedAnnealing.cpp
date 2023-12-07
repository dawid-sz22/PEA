#include "SimulatedAnnealing.h"
#include <iostream>
#include <algorithm>
#include "TabuSearch.h"
#include "../Tools/Timer.h"
#include "../Tools/Generator.h"

SimulatedAnnealing::SimulatedAnnealing(AdjacencyMatrix* matrix, int bestKnownResult, double timeStop,
                                       int neighborhoodType, int iterationMAXNochange, double a, int L):
matrix(matrix), timeStop(timeStop),bestKnownResult(bestKnownResult),timeWhenBest (0.0),neighborhoodType(neighborhoodType),
shortestPath(matrix->getNodesCount() + 1, 0), a(a), L(7*matrix->getNodesCount()),
temperature(500.0), iterationsWithNoChangeMAX(iterationMAXNochange), iterationsWithNoChange(0)
{}


void SimulatedAnnealing::greedyRoute() {
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
    greedyPathValue = shortestPathValue;

    delete[] alreadyVisited;

}


int SimulatedAnnealing::countPath(vector<int> &source) {
    int helpCount = 0;
    for (int i = 0; i < matrix->getNodesCount(); i++) {
        //zliczanie całej wartości ścieżki. Jeśli dojdziemy do ostatniego wierzchołka w ścieżce, policz powrót
        helpCount += matrix->getWsk()[source[i]][source[i+1]];
    }
    return helpCount;
}

int SimulatedAnnealing::countPath(int tempValue, int elementI, int elementJ, std::vector<int> &source) {
    int minus  = 0, plus = 0;

    switch (neighborhoodType) {
        case 1: /// SWAP
            if (abs(elementI - elementJ) > 1) {
                //zmniejsz dotychczasową wartość ścieżki o krawędzie, z którymi uczestniczą zamieniane wierzchołki (PO MOŻLIWEJ ZAMIANIE)
                minus = (matrix->getWsk()[source[elementI - 1]][source[elementI]] +
                         matrix->getWsk()[source[elementI]][source[elementI + 1]]
                         + matrix->getWsk()[source[elementJ - 1]][source[elementJ]] +
                         matrix->getWsk()[source[elementJ]][source[elementJ + 1]]);

                //powiększ wartość ścieżki o krawędzie, z którymi uczestniczą zamieniane wierzchołki (PO MOŻLIWEJ ZAMIANIE)
                plus = (matrix->getWsk()[source[elementI - 1]][source[elementJ]] +
                        matrix->getWsk()[source[elementJ]][source[elementI + 1]]
                        + matrix->getWsk()[source[elementJ - 1]][source[elementI]] +
                        matrix->getWsk()[source[elementI]][source[elementJ + 1]]);
            } else
            {
                //zmniejsz dotychczasową wartość ścieżki o krawędzie, z którymi uczestniczą zamieniane wierzchołki(PO MOŻLIWEJ ZAMIANIE)
                minus = (matrix->getWsk()[source[elementI - 1]][source[elementI]] +
                         matrix->getWsk()[source[elementI]][source[elementI + 1]] +
                         matrix->getWsk()[source[elementJ]][source[elementJ + 1]]);

                //powiększ wartość ścieżki o krawędzie, z którymi uczestniczą zamieniane wierzchołki (PO MOŻLIWEJ ZAMIANIE)
                plus = (matrix->getWsk()[source[elementI - 1]][source[elementJ]] +
                        matrix->getWsk()[source[elementJ]][source[elementI]] +
                        matrix->getWsk()[source[elementI]][source[elementJ + 1]]);
            }
            break;
        case 2: /// INSERT
            //zmniejsz dotychczasową wartość ścieżki o krawędzie, z którymi uczestniczą zamieniane wierzchołki (PO MOŻLIWEJ ZAMIANIE)
            minus = (matrix->getWsk()[source[elementI - 1]][source[elementI]] +
                     matrix->getWsk()[source[elementJ-1]][source[elementJ]]
                     + matrix->getWsk()[source[elementJ]][source[elementJ + 1]]);

            //powiększ wartość ścieżki o krawędzie, z którymi uczestniczą zamieniane wierzchołki (PO MOŻLIWEJ ZAMIANIE)
            plus = (matrix->getWsk()[source[elementI - 1]][source[elementJ]] +
                    matrix->getWsk()[source[elementJ]][source[elementI]]
                    + matrix->getWsk()[source[elementJ - 1]][source[elementJ + 1]]);
            break;
        case 3: ///INVERT
            int max = abs(elementJ - elementI);

            plus += matrix->getWsk()[source[elementI - 1]][source[elementJ]];
            minus += matrix->getWsk()[source[elementI - 1]][source[elementI]];

            for (int i = 0; i < max; ++i) {
                minus += matrix->getWsk()[source[elementI + i]][source[elementI + 1 + i]];
                plus += matrix->getWsk()[source[elementJ - i]][source[elementJ - 1 - i]];
            }

            minus += matrix->getWsk()[source[elementJ]][source[elementJ + 1]];
            plus += matrix->getWsk()[source[elementI]][source[elementJ + 1]];

            break;
    }

    return tempValue - minus + plus;
}

void SimulatedAnnealing::start() {
    Timer timer;
    timeWhenBest = 0.0;

    greedyRoute();

    iterationsWithChange = 0;
    double avg = 0;
    double count = 0;
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        for (int j = 0; j < matrix->getNodesCount(); ++j) {
            if (i!=j)
            {
                avg += matrix->getWsk()[i][j];
                count++;
            }
        }
    }
    avg = avg/count;
    temperature = avg;
    L = matrix->getNodesCount() * matrix->getNodesCount();
    temperatureStart = temperature;
    cout << temperatureStart << ";";

    //Przepisanie najlepszej aktualnej ścieżki do tymczasowej ścieżki
    vector<int> currentRoute(matrix->getNodesCount() + 1,0);
    for (int i = 0; i < matrix->getNodesCount() + 1; ++i) {
        currentRoute[i] = shortestPath[i];
    }

    //rozwiązanie aktualne, dla którego obliczane jest sąsiedztwo
    int currentSolutionValue = shortestPathValue;
    int diff;
    int iTemp, jTemp, help;

    timer.run();

    //wykonuje dopóki nie upłynie ustalony czas
    while (iterationsWithChange == 0) {
        for (int k = 0; k < L; k++) {
            iTemp = generator.getNumber(1,matrix->getNodesCount()-1);
            jTemp = generator.getNumber(1,matrix->getNodesCount()-1);
            while (iTemp == jTemp)
            {
                jTemp = generator.getNumber(1,matrix->getNodesCount()-1);
            }
            if (iTemp > jTemp)
            {
                help = iTemp;
                iTemp = jTemp;
                jTemp = help;
            }

            //różnica pomiędzy wyliczonym rozwiązniem a aktualnym
            diff = countPath(currentSolutionValue,iTemp,jTemp,currentRoute) - currentSolutionValue;

            //zamień bieżącą ścieżke, jesli znaleziono lepsze rozwiązanie od bieżącego
            //LUB w zależności od prawdopodobieństwa, zamień na gorsze rozwiązanie
            if ((diff < 0) || isToChange(diff,temperature)) {
                //dokonaj zmiany ścieżki
                switch (neighborhoodType) {
                    case 1:
                        std::swap(currentRoute[iTemp], currentRoute[jTemp]);
                        break;
                    case 2:
                        insert(currentRoute,jTemp,iTemp);
                        break;
                    case 3:
                        std::reverse(currentRoute.begin() + iTemp, currentRoute.begin() + jTemp + 1);
                        break;
                }
                //zaktualizuj koszt
                currentSolutionValue += diff;

                //sprawdź, czy nie jest lepsze od aktualnego optimum -->> jeśli tak to zapisz najlepsze dotychczasowe rozwiązanie
                if (currentSolutionValue < shortestPathValue) {
                    timeWhenBest = timer.readMs();
                    shortestPathValue = currentSolutionValue;
                    shortestPath = currentRoute;
                    shortestPathChanging.push_back({static_cast<double>(shortestPathValue),(timer.readMs())});
                    iterationsWithChange++;
                }
            }
        }
        ///SCHŁADZANIE
        temperature *= a;
        if (temperature < 0.00000001 && iterationsWithChange <3)
        {
            currentRoute = shortestPath;
            randomRoute(currentRoute);
            currentSolutionValue = countPath(currentRoute);
            temperature = generator.getNumber(50,500);
            temperatureStart = temperature;
//            cout << "Here"<< endl;
        }
        else if (iterationsWithChange > 0)
            cout << temperatureStart << ";";
    }
}

void SimulatedAnnealing::printResults() {
    cout << "SCIEZKA\n ";
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        cout << shortestPath[i] << " -> ";
    }
    cout << shortestPath[matrix->getNodesCount()];
    cout << "\nKOSZT (METODA ZACHLANNA): " <<greedyPathValue;
    cout << "\nKOSZT (NAJLEPSZA ZNALEZIONA): " <<shortestPathValue;
    if (bestKnownResult != -1)
        cout << "\nBLAD WZGLEDNY: " <<(abs(shortestPathValue-bestKnownResult)/(double)bestKnownResult)*100<<"%  (BEST: "<<bestKnownResult<<")";
    cout << "\nCZAS W JAKIM ZNALEZIONO ROZWIAZANIE: " <<timeWhenBest <<"ms";
    cout << "\nEXP(-1/Tk): " <<exp(-1/temperature);
    cout << "\nTk: " <<temperature;
    cout << endl;
}

int SimulatedAnnealing::getPathValue() {
    return shortestPathValue;
}

void SimulatedAnnealing::randomRoute(vector<int> &source) {
    Generator gen;
    vector<int> helpVector;
    int randomPosition;


    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        if (matrix->getStartNode() == i)
            continue;

        helpVector.push_back(i);
    }
    source[0] = matrix->getStartNode();
    for (int i = 1; i < matrix->getNodesCount(); ++i) {
        randomPosition = gen.getNumber(0,(int)helpVector.size() - 1);
        source[i] = helpVector.at(randomPosition);
        helpVector.erase(helpVector.begin() + randomPosition);
    }
    source[matrix->getNodesCount()] = matrix->getStartNode();

//    if (gen.getNumber(0,1))
//    {
//        for (int i = 0; i < matrix->getNodesCount()/2; ++i) {
//            if (matrix->getStartNode() == i)
//                continue;
//
//            helpVector.push_back(source[i]);
//        }
//
//        for (int i = 1; i < matrix->getNodesCount()/2; ++i) {
//            randomPosition = gen.getNumber(0,(int)helpVector.size() - 1);
//            source[i] = helpVector.at(randomPosition);
//            helpVector.erase(helpVector.begin() + randomPosition);
//        }
//    }
//    else //jeśli 1 to losuj drugą część ścieżki
//    {
//        for (int i = matrix->getNodesCount()/2; i < matrix->getNodesCount(); ++i) {
//            helpVector.push_back(source[i]);
//        }
//
//        for (int i = matrix->getNodesCount()/2; i < matrix->getNodesCount(); ++i) {
//            randomPosition = gen.getNumber(0,(int)helpVector.size() - 1);
//            source[i] = helpVector.at(randomPosition);
//            helpVector.erase(helpVector.begin() + randomPosition);
//        }
//    }

}

vector<int> SimulatedAnnealing::getShortestPath() {
    return shortestPath;
}

int SimulatedAnnealing::getTime() {
    return timeWhenBest;
}

void SimulatedAnnealing::insert(std::vector<int> &v, int oldIndex, int newIndex) {
    if (oldIndex > newIndex)
        rotate(v.rend() - oldIndex - 1, v.rend() - oldIndex, v.rend() - newIndex);
    else
        rotate(v.begin() + oldIndex, v.begin() + oldIndex + 1, v.begin() + newIndex + 1);
}

std::vector<std::vector<double>> SimulatedAnnealing::getPathChanging() {
    return shortestPathChanging;
}

bool SimulatedAnnealing::isToChange(int diff, double temp) {
    return exp(diff/temp) >= generator.randomZeroToOne();
}


