#ifndef UNTITLED_SIMULATEDANNEALING_H
#define UNTITLED_SIMULATEDANNEALING_H
#include "../Graphs/AdjacencyMatrix.h"
#include "../Tools/TabuElement.h"
#include "../Tools/Generator.h"
#include <vector>
#include <random>

class SimulatedAnnealing {
    AdjacencyMatrix* matrix;
    std::vector<int> shortestPath;
    std::vector<std::vector<double>> shortestPathChanging;
    int shortestPathValue;
    int greedyPathValue;
    double timeStop;
    double timeWhenBest;
    int neighborhoodType;    ///1 -  SWAP ; 2 - INSERT ; 3 - INVERT
    int bestKnownResult;    //znane optymalne rozwiązanie, do porównania wyników
    int iterationsWithChange;
    double temperature;
    double temperatureStart;
    int L;                  //długość epoki
    double a;               //współczynnik schładzanie (Temp + 1 = a*temp), gdzie a < 1
    Generator generator;    //losowanie

public:
    SimulatedAnnealing(AdjacencyMatrix* matrix, int bestKnownResult, double timeStop, int neighborhoodType, double a);
    void greedyRoute();
    void start();
    int countPath(int tempValue, int I, int J, std::vector<int> &source);
    int countPath(std::vector<int> &source);
    void printResults();
    int getPathValue();
    double getTempStart();
    double getTempEnd();
    int getL();
    std::vector<int> getShortestPath();
    int getTime();
    std::vector<std::vector<double>> getPathChanging();
    void insert(std::vector<int>& v, int oldIndex, int newIndex);
    bool isToChange(int diff, double temp);
    void randomRoute(vector<int> &source);
};

#endif //UNTITLED_SIMULATEDANNEALING_H
