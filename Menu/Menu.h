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
    static void autoTS(std::string data[],int timeData[], int iterationsNoChange, int dataCount, int typeNeighborhood);

};


#endif //SDIZO2_MENU_H
