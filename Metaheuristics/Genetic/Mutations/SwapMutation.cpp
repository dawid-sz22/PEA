#include "SwapMutation.h"

void SwapMutation::doMutation(Tour &tour) {
    int n1 = generator.getNumber(1,tour.getSize() - 2);
    int n2 = generator.getNumber(1,tour.getSize() - 2);

    while (n1 == n2)
        n2 = generator.getNumber(1,tour.getSize() - 2);
    std::swap(tour.nodes[n1], tour.nodes[n2]);

    tour.correctFitness(matrix);
}
