#ifndef UNTITLED_SWAPMUTATION_H
#define UNTITLED_SWAPMUTATION_H
#include "MutationStrategy.h"

class SwapMutation : public MutationStrategy{
public:
    void doMutation(Tour &tour) override;
};


#endif //UNTITLED_SWAPMUTATION_H
