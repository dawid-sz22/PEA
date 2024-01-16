#ifndef SDIZO2_MENU_H
#define SDIZO2_MENU_H


#include "../Graphs/AdjacencyMatrix.h"
#include "../Tools/Timer.h"
#include <fstream>
#include <vector>

using namespace std;

class Menu {
public:
    static void showMenuManual();
    static void showMenuManualM();
    static void showMenuManualGA();
    static void showMenu();
    static void showMenuAutomatic();
    static void autoBF(int* data, int dataCount);
    static void autoBB(int* data, int dataCount);
    static void autoDP(int* data, int dataCount);
    static void autoTS(std::string data[], int timeData[], int iterationsNoChange, double k, int dataCount, int typeNeighborhood, int aspiration);
    static void autoSA(std::string data[], int timeData[], double* a, int typeNeighborhood, int dataCount);
    static void autoGA(vector<string>& data, const vector<int>& timeData, const vector<int>& populationSize,
                      const vector<string>& mutationStrategy, const vector<double>& mutationRate, const vector<string>& crossStrategy,
                      const vector<double>& crossRate, int bestKnown, int iterations);
};


#endif //SDIZO2_MENU_H
