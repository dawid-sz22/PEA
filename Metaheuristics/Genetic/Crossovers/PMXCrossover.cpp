#include "PMXCrossover.h"
#include <vector>
#include <algorithm>

void PMXCrossover::doCrossover(Tour &parent1, Tour &parent2) {

    ///CHILD1
    std::vector<int> child(parent1.nodes.size(), -1);
    int begin = generator.getNumber(1, parent1.getSize() - 2);
    int end = generator.getNumber(1, parent1.getSize() - 1);

    while (begin == end)
        end = generator.getNumber(1, parent1.getSize() - 1);

    if (begin > end)
        swap(begin, end);

    std::copy(parent1.nodes.begin() + begin, parent1.nodes.begin() + end, child.begin() + begin);

    for (int i = begin; i < end; ++i) {
        if (std::find(child.begin(), child.end(), parent2.nodes[i]) == child.end()) {
            int current_index = i;
            while (current_index >= begin && current_index < end) {
                current_index = std::distance(parent2.nodes.begin(), std::find(parent2.nodes.begin(), parent2.nodes.end(), parent1.nodes[current_index]));
            }
            child[current_index] = parent2.nodes[i];
        }
    }

    for (int i = 0; i < child.size(); ++i) {
        if (child[i] == -1) {
            child[i] = parent2.nodes[i];
        }
    }


    ///CHILD2
    std::vector<int> child2(parent1.nodes.size(), -1);
    begin = generator.getNumber(1, parent1.getSize() - 2);
    end = generator.getNumber(1, parent1.getSize() - 1);

    while (begin == end)
        end = generator.getNumber(1, parent1.getSize() - 1);

    if (begin > end)
        swap(begin, end);

    std::copy(parent2.nodes.begin() + begin, parent2.nodes.begin() + end, child2.begin() + begin);

    for (int i = begin; i < end; ++i) {
        if (std::find(child2.begin(), child2.end(), parent1.nodes[i]) == child2.end()) {
            int current_index = i;
            while (current_index >= begin && current_index < end) {
                current_index = std::distance(parent1.nodes.begin(), std::find(parent1.nodes.begin(), parent1.nodes.end(), parent2.nodes[current_index]));
            }
            child2[current_index] = parent1.nodes[i];
        }
    }

    for (int i = 0; i < child.size(); ++i) {
        if (child2[i] == -1) {
            child2[i] = parent1.nodes[i];
        }
    }

    parent1.nodes = child;
    parent2.nodes = child2;

    parent1.correctFitness(matrix);
    parent2.correctFitness(matrix);
}
