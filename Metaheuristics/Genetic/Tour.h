#ifndef UNTITLED_TOUR_H
#define UNTITLED_TOUR_H

#include <vector>
#include "../../Graphs/AdjacencyMatrix.h"

class Tour {
    int fitness;
public:
    std::vector<int> nodes;

    Tour(Tour &tour, AdjacencyMatrix* matrix);
    Tour(std::vector<int>& nodes);
    Tour(int size, AdjacencyMatrix* matrix);
    Tour();
    int getFitness();
    void correctFitness(AdjacencyMatrix* matrix);
    int getSize();
    void setNode(int postion, int node);
};


#endif //UNTITLED_TOUR_H
