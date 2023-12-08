#ifndef SDIZO2_MENU_H
#define SDIZO2_MENU_H


#include "../Graphs/AdjacencyMatrix.h"
#include "../Tools/Timer.h"
#include <fstream>

class Menu {
public:
    static void showMenuManual();
    static void showMenuManualM();
    static void showMenu();
    static void showMenuAutomatic();
    static void autoBF(int* data, int dataCount);
    static void autoBB(int* data, int dataCount);
    static void autoDP(int* data, int dataCount);
    static void autoTS(std::string data[], int timeData[], int iterationsNoChange, double k, int dataCount, int typeNeighborhood, int aspiration);
    static void autoSA(std::string data[], int timeData[], double* a, int typeNeighborhood, int dataCount);

};


#endif //SDIZO2_MENU_H
