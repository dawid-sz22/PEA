#include "InsertMutation.h"
#include <algorithm>
void InsertMutation::doMutation(Tour &tour) {
    int oldIndex = generator.getNumber(1,tour.getSize() - 2);
    int newIndex = generator.getNumber(1,tour.getSize() - 2);

    while (oldIndex == newIndex)
        newIndex = generator.getNumber(1,tour.getSize() - 2);

    if (oldIndex > newIndex)
        rotate(tour.nodes.rend() - oldIndex - 1, tour.nodes.rend() - oldIndex, tour.nodes.rend() - newIndex);
    else
        rotate(tour.nodes.begin() + oldIndex, tour.nodes.begin() + oldIndex + 1, tour.nodes.begin() + newIndex + 1);

    tour.correctFitness(matrix);
}
