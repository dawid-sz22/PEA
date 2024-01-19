#ifndef UNTITLED_GENETICALGORITHM_H
#define UNTITLED_GENETICALGORITHM_H

#include "Crossovers/CrossoverStrategy.h"
#include "Crossovers/PMXCrossover.h"
#include "Crossovers/OXCrossover.h"
#include "../../Tools/Timer.h"
#include "Population.h"
#include "Mutations/MutationStrategy.h"
#include "Mutations/InsertMutation.h"
#include <string>

class GeneticAlgorithm {
public:
    AdjacencyMatrix* matrix;
    double mutationRate;
    double crossRate;
    int tournamentSize;
    int populationSize;
    double stopTime;
    CrossoverStrategy* crossoverStrategy;
    MutationStrategy* mutationStrategy;
    int bestCost;
    int bestKnownResult;
    Tour bestTour;
    Population population;
    std::vector<std::vector<double>> shortestPathChanging;
    double bestValueTime;
    double error;

    GeneticAlgorithm(AdjacencyMatrix* matrix, double mutationRate, double crossRate, int populationSize, const std::string& crossoverStrategy,const std::string& mutationStrategy, double stopTime, int bestKnownResult);
    void startAlgorithm();
    void checkBestTour(double time);
    void selection(Population &parentalPopulation);
    void crossoverAndMutation(Population &parentalPopulation, Population &newPopulation);
    static bool compareTour(Tour &t1, Tour &t2);
    void printResults();

};


#endif //UNTITLED_GENETICALGORITHM_H
