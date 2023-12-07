#ifndef SDIZO_GENERATOR_H
#define SDIZO_GENERATOR_H
#include <random>
#include <iostream>
using namespace std;

class Generator {
    random_device rd;
    mt19937 gen;
    uniform_int_distribution<> dist;
    uniform_real_distribution<> distDouble;
public:
    Generator();
    int getNumber();
    int getNumber(int min, int max);
    double randomZeroToOne();
};


#endif //SDIZO_GENERATOR_H
