#include "OXCrossover.h"
#include <algorithm>
#include <iostream>
void OXCrossover::doCrossover(Tour &child1, Tour &child2) {

    int begin = generator.getNumber(1, child1.getSize() - 2);
    int end = generator.getNumber(1, child1.getSize() - 2);

    while (begin == end)
        end = generator.getNumber(1, child1.getSize() - 2);

    if (begin > end)
        swap(begin, end);

    Tour parent1(child1.nodes);
    Tour parent2(child2.nodes);

    bool found1A = false;
    bool found2A = false;
    //Ustawienie indeksu sciezki potomnej
    int childIndex = end + 1;
    if (childIndex == child1.getSize() - 1) childIndex = 1;
    int childIndex2 = childIndex;
    //Ustawienie indeksu sciezki rodzica
    int parentIndex = childIndex;
    int parentIndex2 = childIndex;
    //Glowna petla krzyzowania trwa do momentu wypelnienia sciezki potomnej
    while (true) {

        //Zmienna przechowuje stan znalezienia danego miasta z rodzica w skopiowanej czesci
        bool found1 = false;
        bool found2 = false;
        //Szukanie danego miasta z rodzica w skopiowanej czesci
        for (int i = begin; i <= end; i++)
        {
            if (parent2.nodes[parentIndex2] == child1.nodes[i])
                found2 = true;
            if (parent1.nodes[parentIndex] == child2.nodes[i])
                found1 = true;

            if (found2 && found1)
                break;
        }
        if (childIndex != begin)
        {
            //Jezeli rozpatrywane miasto rodzica nie wystepuje w skopiowanej czesci to jest przepisane do potomka
            if (!found2)
            {
                child1.nodes[childIndex] = parent2.nodes[parentIndex2];
                childIndex++;

                if (childIndex == child1.getSize() - 1)
                    childIndex = 1;
            }
        } else found1A = true;
        if (childIndex2 != begin) {
            if (!found1) {
                child2.nodes[childIndex2] = parent1.nodes[parentIndex];
                childIndex2++;

                if (childIndex2 == child2.getSize() - 1)
                    childIndex2 = 1;
            }
        } else found2A = true;

        if (found1A && found2A)
            break;
        //Rozpatrujemy kolejne miasto rodzica
        parentIndex++;
        parentIndex2++;
        if (parentIndex == child2.getSize() - 1)
            parentIndex = 1;
        if (parentIndex2 == child2.getSize() - 1)
            parentIndex2 = 1;
    }

    child1.correctFitness(matrix);
    child2.correctFitness(matrix);
}
