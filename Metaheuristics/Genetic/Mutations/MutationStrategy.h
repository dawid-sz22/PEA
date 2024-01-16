#ifndef UNTITLED_MUTATIONSTRATEGY_H
#define UNTITLED_MUTATIONSTRATEGY_H


#include "../Tour.h"
#include "../../../Tools/Generator.h"

class MutationStrategy {
public:
    Generator generator;
    static AdjacencyMatrix* matrix;
    virtual void doMutation(Tour &tour) = 0;
};


#endif //UNTITLED_MUTATIONSTRATEGY_H
