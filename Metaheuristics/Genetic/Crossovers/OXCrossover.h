#ifndef UNTITLED_OXCROSSOVER_H
#define UNTITLED_OXCROSSOVER_H
#include "CrossoverStrategy.h"

class OXCrossover : public CrossoverStrategy{
public:
    void doCrossover(Tour &child1, Tour &child2) override;
};


#endif //UNTITLED_OXCROSSOVER_H
