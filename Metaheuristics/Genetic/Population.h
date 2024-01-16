#ifndef UNTITLED_POPULATION_H
#define UNTITLED_POPULATION_H

#include <vector>
#include "Tour.h"

class Population {
    std::vector<Tour> tours;
    int sizePopulation;
    AdjacencyMatrix* matrix;

public:
    Population(int size,int sizeTour, AdjacencyMatrix* matrix);
    Population(AdjacencyMatrix* matrix);
    std::vector<Tour>* getTours();
    int getSize();
    Tour getBestTour();
    void addTour(Tour &tour);
};


#endif //UNTITLED_POPULATION_H
