#include "Tour.h"

#include "../../Tools/Generator.h"

int Tour::getFitness() {
    return fitness;
}

int Tour::getSize() {
    return nodes.size();
}

Tour::Tour(Tour &tour, AdjacencyMatrix* matrix) {
    nodes = tour.nodes;

    correctFitness(matrix);
}
Tour::Tour(std::vector<int>& nodes) {
    this->nodes = nodes;

    fitness = -1;
}
Tour::Tour(int size, AdjacencyMatrix* matrix) {
    Generator gen;
    vector<int> helpVector;
    int randomPosition;
    nodes.resize(size + 1);

    nodes[0] = 0;

    for (int i = 1; i < size; ++i) {
        helpVector.push_back(i);
    }

    //tworzenie losowej ścieżki
    for (int i = 1; i < size; ++i) {
        randomPosition = gen.getNumber(0,(int)helpVector.size() - 1);
        nodes[i] = helpVector.at(randomPosition);
        helpVector.erase(helpVector.begin() + randomPosition);
    }

    nodes[size] = 0;

    correctFitness(matrix);
}

void Tour::setNode(int postion, int node) {
    nodes[postion] = node;
}

Tour::Tour() {

}

void Tour::correctFitness(AdjacencyMatrix* matrix) {
    int helpCount = 0;

    for (int i = 0; i < matrix->getNodesCount(); i++) {
        //zliczanie całej wartości ścieżki
        helpCount += matrix->getWsk()[nodes[i]][nodes[i+1]];
    }

    fitness = helpCount;
}

