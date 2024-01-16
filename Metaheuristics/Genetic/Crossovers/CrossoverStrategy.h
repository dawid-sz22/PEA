#ifndef UNTITLED_CROSSOVERSTRATEGY_H
#define UNTITLED_CROSSOVERSTRATEGY_H

#include "../Tour.h"
#include "../../../Tools/Generator.h"

class CrossoverStrategy {
public:
    Generator generator;
    static AdjacencyMatrix* matrix;
    virtual void doCrossover(Tour &parent1, Tour &parent2) = 0;
};


#endif //UNTITLED_CROSSOVERSTRATEGY_H
