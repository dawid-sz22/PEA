#include "GeneticAlgorithm.h"
#include "Mutations/SwapMutation.h"
#include <iostream>
#include <bits/stdc++.h>
GeneticAlgorithm::GeneticAlgorithm(AdjacencyMatrix *matrix, double mutationRate, double crossRate,
                                   int populationSize, const std::string& crossoverStrategy,const std::string& mutationStrategy, double stopTime,
                                   int bestKnownResult):mutationRate(mutationRate),
                                   crossRate(crossRate), tournamentSize ((int)(populationSize*0.3)), populationSize(populationSize),
                                   matrix(matrix), stopTime(stopTime), bestTour(), bestKnownResult(bestKnownResult),
                                                        population(nullptr)
{
    /// WYBÓR METODY KRZYŻOWANIA
    if (crossoverStrategy == "PMX")
        this->crossoverStrategy = new PMXCrossover();
    else if (crossoverStrategy == "OX")
        this->crossoverStrategy = new OXCrossover();

    CrossoverStrategy::matrix = matrix;

    /// WYBÓR METODY MUTACJI
    if (mutationStrategy == "INSERT")
        this->mutationStrategy = new InsertMutation();
    else if (mutationStrategy == "SWAP")
        this->mutationStrategy = new SwapMutation();

    MutationStrategy::matrix = matrix;


    population = Population(populationSize, matrix->getNodesCount(), matrix);
    checkBestTour(0);

    bestCost = INT32_MAX;
}

void GeneticAlgorithm::startAlgorithm() {
    Timer timer;

    timer.run();
    while (timer.readS() < stopTime)
    {
        Population newPopulation(matrix);
        Population parentalPopulation(matrix);

        ///10% BEST TO NEW
        //sortowanie populacji
        sort(population.getTours()->begin(), population.getTours()->end(), compareTour);
        //10% populacji (najlepszych tras) przechodzi do nowej
        for (int i = 0; i < populationSize / 10; ++i) {
            newPopulation.addTour(population.getTours()->at(i));
        }

        ///SELEKCJA DO PULI MACIERZYSTEJ
        selection(parentalPopulation);

        ///KRZYŻOWANIE I MUTACJA W PULI MACIERZYSTEJ ORAZ DODANIE GENEOTYPÓW DO NOWEJ POPULACJI
        crossoverAndMutation(parentalPopulation, newPopulation);

        ///PRZEPISANIE
        population = newPopulation;

        /// OCENA
        checkBestTour(timer.readMs());
    }

}

void GeneticAlgorithm::checkBestTour(double time) {
    /// OCENA
    Tour helpTour;
    int helpBest;
    helpTour = population.getBestTour();
    helpBest = helpTour.getFitness();
    if (bestCost > helpBest)
    {
        bestCost = helpBest;
        bestTour = helpTour;
        shortestPathChanging.push_back({static_cast<double>(bestCost),(time)});
        bestValueTime = time;
    }
}

void GeneticAlgorithm::selection(Population &parentalPopulation) {
    Generator generator;
    int helpCost = INT32_MAX;
    int helpCostTour;
    int indexRandom;
    Tour* helpTour;

    /// SELEKCJA TURNIEJOWA
    //wybieramy trasy do puli macierzystej (rozmiar puli to 90% populacji, gdyż 10% przechodzi z góry)
    for (int i = 0; i < populationSize - (populationSize / 10); ++i) {
        helpCost = INT32_MAX;

        //wybierz najlepszego z turnieju
        for (int j = 0; j < tournamentSize; ++j) {
            indexRandom = generator.getNumber(0,populationSize - 1);
            helpCostTour = population.getTours()->at(indexRandom).getFitness();
            if (helpCostTour < helpCost)
            {
                helpCost = helpCostTour;
                helpTour = &population.getTours()->at(indexRandom);
            }
        }

        //dodaj zwycięzce do puli macierzystej
        parentalPopulation.addTour(*helpTour);
    }

}


bool GeneticAlgorithm::compareTour(Tour &t1, Tour &t2)
{
    return (t1.getFitness() < t2.getFitness());
}

void GeneticAlgorithm::crossoverAndMutation(Population &parentalPopulation, Population &newPopulation) {
    Generator generator;
    int indexRandom1;
    int indexRandom2;
    int newPopulationSize = newPopulation.getSize();
    for (int i = 0; i < (populationSize - newPopulationSize)/2; ++i) {
        indexRandom1 = generator.getNumber(0,parentalPopulation.getSize()-1);
        indexRandom2 = generator.getNumber(0,parentalPopulation.getSize()-1);

        //zabezpieczenie przed wylosowaniem tego samego genotypu
        while (indexRandom1 == indexRandom2)
            indexRandom2 = generator.getNumber(0,parentalPopulation.getSize()-1);

        Tour newTour1(parentalPopulation.getTours()->at(indexRandom1));
        Tour newTour2(parentalPopulation.getTours()->at(indexRandom2));

        //według podanego prawdopodobieństwa, robimy krzyżowanie osobników lub też nie
        if (generator.randomZeroToOne() <= crossRate)
        {
            // z 2 rodziców powstaje 2 dzieci
            crossoverStrategy->doCrossover(newTour1, newTour2);
        }

        ///MUTACJE
        if (generator.randomZeroToOne() <= mutationRate)
            mutationStrategy->doMutation(newTour1);
        if (generator.randomZeroToOne() <= mutationRate)
            mutationStrategy->doMutation(newTour2);
        newPopulation.addTour(newTour1);
        newPopulation.addTour(newTour2);
    }

    if (newPopulation.getSize() < populationSize)
        newPopulation.addTour(parentalPopulation.getTours()->at(generator.getNumber(0,parentalPopulation.getSize()-1)));

}

void GeneticAlgorithm::printResults() {
    cout << "SCIEZKA\n ";
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        cout << bestTour.nodes[i] << " -> ";
    }
    cout << bestTour.nodes[matrix->getNodesCount()];
    cout << "\nKOSZT (NAJLEPSZA ZNALEZIONA): " <<bestCost;
    if (bestKnownResult != -1)
        cout << "\nBLAD WZGLEDNY: " <<(abs(bestCost-bestKnownResult)/(double)bestKnownResult)*100<<"%  (BEST: "<<bestKnownResult<<")";
    cout << endl;
}

