#ifndef UNTITLED_PMXCROSSOVER_H
#define UNTITLED_PMXCROSSOVER_H

#include "CrossoverStrategy.h"
class PMXCrossover : public CrossoverStrategy{
public:
    void doCrossover(Tour &parent1, Tour &parent2) override;
};


#endif //UNTITLED_PMXCROSSOVER_H
