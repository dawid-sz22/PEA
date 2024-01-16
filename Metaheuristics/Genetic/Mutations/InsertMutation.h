#ifndef UNTITLED_INSERTMUTATION_H
#define UNTITLED_INSERTMUTATION_H


#include "MutationStrategy.h"

class InsertMutation : public MutationStrategy{
public:
    void doMutation(Tour &tour) override;
};


#endif //UNTITLED_INSERTMUTATION_H
