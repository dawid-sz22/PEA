#include "Population.h"
#include "Tour.h"
#include <iostream>
std::vector<Tour>* Population::getTours() {
    return &tours;
}

int Population::getSize() {
    return sizePopulation;
}

Population::Population(int sizePopulation, int sizeTour, AdjacencyMatrix* matrix) : sizePopulation(sizePopulation), matrix(matrix){
    for (int i = 0; i < sizePopulation; ++i) {
        tours.emplace_back(sizeTour,matrix);
    }
}

Tour Population::getBestTour() {
    int best = INT32_MAX;
    int help = 0;
    Tour tourBest;

    //szukanie najlepszej drogi
    for (Tour tour : tours) {
        help = tour.getFitness();
        if (best > help)
        {
            best = help;
            tourBest = tour;
        }
    }

    return tourBest;
}

Population::Population(AdjacencyMatrix* matrix) : matrix(matrix) {
    sizePopulation = 0;
}

void Population::addTour(Tour &tour) {
    tours.push_back(tour);
    sizePopulation++;
}
