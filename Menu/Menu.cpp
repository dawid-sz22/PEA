#include "Menu.h"
#include "../Tools/FileClass.h"
#include "../Algorithms/BranchAndBound.h"
#include "../Algorithms/BruteForce.h"
#include "../Algorithms/DynamicPrograming.h"
#include "../Metaheuristics/TabuSearch.h"
#include "../Metaheuristics/SimulatedAnnealing.h"
#include "../Metaheuristics/Genetic/GeneticAlgorithm.h"
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

void Menu::showMenu()
{
    int choose;
    do {
        cout << "Asymetryczny problem komiwojazera (ATSP)\n";
        cout << "1. Testy manualne (Algorytmy dokladne)\n";
        cout << "2. Testy manualne (Tabu Search. SimulatedAnnealing)\n";
        cout << "3. Testy manualne (Genetic Algorithm)\n";
        cout << "4. Testy automatyczne\n";
        cout << "0. Zakoncz program\n";
        cout << "Wybierz opcje: ";

        cin >> choose; //wybrana opcja

        switch (choose)
        {
            case 1:
                Menu::showMenuManual();
                break;
            case 2:
                Menu::showMenuManualM();
                break;
            case 3:
                Menu::showMenuManualGA();
                break;
            case 4:
                Menu::showMenuAutomatic();
                break;
            case 0:
                break;
            default:
                cout << endl << "Podano nieprawidlowa opcje!" << endl;
                break;
        }
    } while (choose);
}

void Menu::showMenuAutomatic() {
    int chooseOption = 0;
    int dataCount = 0;

    do
    {
        cout << "1. Brute Force\n";
        cout << "2. Branch&Bound\n";
        cout << "3. DynamicPrograming\n";
        cout << "4. All\n";
        cout << "5. Tabu Search\n";
        cout << "6. SA\n";
        cout << "7. GA\n";
        cout << "0. Wroc\n";
        cout << "Wybierz opcje: ";
        cin >> chooseOption; //wybrana opcje

        switch (chooseOption)
        {
            case 1: //Brute Force
            {
                cout << "Podaj rozmiar problemu (X problemow po 100 losowych reprezentacji) : ";
                cin >> dataCount;
                int* data = new int [dataCount];

                for (int i = 0; i < dataCount; ++i) {
                    cout << i+1 << ": ";
                    cin >> data[i];
                }
                autoBF(data,dataCount);
            }
                break;
            case 2: //Branch&Bound
            {
                cout << "Podaj rozmiar problemu (X problemow po 100 losowych reprezentacji) : ";
                cin >> dataCount;
                int* data = new int [dataCount];

                for (int i = 0; i < dataCount; ++i) {
                    cout << i+1 << ": ";
                    cin >> data[i];
                }
                autoBB(data,dataCount);
            }
                break;
            case 3: //DP
            {
                cout << "Podaj rozmiar problemu (X problemow po 100 losowych reprezentacji) : ";
                cin >> dataCount;
                int* data = new int [dataCount];

                for (int i = 0; i < dataCount; ++i) {
                    cout << i+1 << ": ";
                    cin >> data[i];
                }
                autoDP(data,dataCount);
            }
            case 4: //all
            {
                int dataCountBF = 0;
                int dataCountBB = 0;
                int dataCountDP = 0;


                cout << "Podaj rozmiar problemu (X problemow po 100 losowych reprezentacji) dla BruteForce: ";
                cin >> dataCountBF;
                int* dataBF = new int [dataCountBF];

                for (int i = 0; i < dataCountBF; ++i) {
                    cout << i+1 << ": ";
                    cin >> dataBF[i];
                }

                cout << "Podaj rozmiar problemu (X problemow po 100 losowych reprezentacji) dla DynamicPrograming: ";
                cin >> dataCountDP;
                int* dataDP = new int [dataCountDP];

                for (int i = 0; i < dataCountDP; ++i) {
                    cout << i+1 << ": ";
                    cin >> dataDP[i];
                }

                cout << "Podaj rozmiar problemu (X problemow po 100 losowych reprezentacji) dla Branch&Bound: ";
                cin >> dataCountBB;
                int* dataBB = new int [dataCountBB];


                for (int i = 0; i < dataCountBB; ++i) {
                    cout << i+1 << ": ";
                    cin >> dataBB[i];
                }


                autoBF(dataBF,dataCountBF);
                autoDP(dataDP,dataCountDP);
                autoBB(dataBB,dataCountBB);
            }
                break;
            case 5:
            {
                int typeNeighborhood = 1;
                int k = 1;
                int iterations = 1;
                int aspiration = 0;
                string fileNames[] = {"../Files/ftv55.atsp","../Files/ftv170.atsp","../Files/rbg358.atsp"};
                int timeData[] = {120,240,360};
//                int timeData[] = {10,20,30};
                cout << "\nPodaj typ sąsiedztwa (1-SWAP,2-INSERT,3-INVERT,0-ALL): ";
                cin >> typeNeighborhood;
                if (typeNeighborhood<0 || typeNeighborhood>3)
                {
                    typeNeighborhood = 1;
                    cout << endl << "Podano niepoprawna opcje!" << endl;
                    break;
                }
                cout << "\nPodaj max iteracji bez zmian: ";
                cin >> iterations;
                cout << "\nPodaj k: ";
                cin >> k;
                cout << "\nPodaj aspiracje: ";
                cin >> aspiration;
                autoTS(fileNames, timeData, iterations, k, 1, typeNeighborhood, aspiration);
            }
                break;
            case 6:
            {
                int typeNeighborhood = 1;
                int iterations = 1;
                string fileNames[] = {"../Files/ftv55.atsp","../Files/ftv170.atsp","../Files/rbg358.atsp"};
                int timeData[] = {120,240,360};
                double a[] = {0.99,0.999,0.9999};
//                int timeData[] = {240};
                cout << "\nPodaj a (1-0.99,2-0.999,3-0.9999,0-ALL): ";
                cin >> typeNeighborhood;
                if (typeNeighborhood<0 || typeNeighborhood>3)
                {
                    typeNeighborhood = 1;
                    cout << endl << "Podano niepoprawna opcje!" << endl;
                    break;
                }
                cout << "\nPodaj max iteracji bez zmian: ";
                cin >> iterations;
                autoSA(fileNames, timeData,a,typeNeighborhood,3);
            }
                break;
            case 7:
            {
                int typeNeighborhood = 1;
                int iterations = 1;
                int option = 1;
                int optiondata = 1;
                vector<string> data = {"../Files/ftv47.atsp","../Files/ftv170.atsp","../Files/rbg403.atsp"};
                vector<int> timeData = {120,240,360};
                vector<int> populationSize = {};
                vector<string> mutationStrategy = {"INSERT","SWAP"};
                vector<double> mutationRate = {0.01,0.05,0.10};
                vector<string> crossStrategy = {"OX"};
                vector<double> crossRate = {0.8,0.5,0.7,0.9};
                int bestKnown = 0;
                cout << "\nPodaj max iteracji bez zmian: ";
                cin >> iterations;
                cout << "MENU AUTO \n";
                cout << "1. CR=0.8, MR=0.01, POP=ALL3, MS=ALL, CS=ALL\n";
                cout << "2. CR=0.8, MR=ALL3, POP=BESTfrom1, MS=BEST, CS=BEST\n";
                cout << "3. CR=ALL3, MR=0.01, POP=BESTfrom1, MS=BEST, CS=BEST\n";
                cout << "4. DATA (";
                for (const string& dataE: data) {
                    cout << dataE << ";";
                }
                cout << endl;
                cin >> option;
                switch (option) {
                    case 1:
                        autoGA(data, timeData,populationSize,mutationStrategy,{mutationRate[0]},
                               crossStrategy, {crossRate[0]}, bestKnown, iterations);
                        break;
                    case 2:
                        autoGA(data, timeData,{populationSize[0]},{mutationStrategy[0]},
                               mutationRate,{crossStrategy[0]}, {crossRate[0]}, bestKnown, iterations);
                        break;
                    case 3:
                        autoGA(data, timeData,{populationSize[0]},{mutationStrategy[0]},
                               {mutationRate[0]},{crossStrategy[0]}, {crossRate[1],crossRate[2],crossRate[3]},
                               bestKnown, iterations);
                        break;
                    case 4:
                        cout << "1. ftv47\n";
                        cout << "2. ftv170\n";
                        cout << "3. rbg403\n";
                        cout << "4. ALL";
                        cin >> optiondata;
                        switch (optiondata) {
                            case 1:
                                data = {"../Files/ftv47.atsp"};
                                timeData = {120};
                                break;
                            case 2:
                                data = {"../Files/ftv170.atsp"};
                                timeData = {240};
                                break;
                            case 3:
                                data = {"../Files/rbg403.atsp"};
                                timeData = {360};
                                break;
                            case 4:
                                data = {"../Files/ftv47.atsp","../Files/ftv170.atsp","../Files/rbg403.atsp"};
                                timeData = {120,240,360};
                                break;
                            default:
                                cout <<" ZLY NUMER\n";
                                break;
                        }
                    default:
                        cout <<" ZLY NUMER\n";
                        break;
                }
            }
                break;
            case 0:
                system("cls");
                break;
            default:
                cout << endl << "Podano niepoprawna opcje!" << endl;
                break;
        }
        cout << endl;
    } while (chooseOption);
}

void Menu::showMenuManual() {
    AdjacencyMatrix* matrix = nullptr;
    Timer timer;
    int chooseOption = 0;
    int help = 0;

    do
    {
        cout << "1. Wczytaj graf z pliku\n";
        cout << "2. Wygeneruj graf losowo\n";
        cout << "3. Wyswietl graf\n";
        cout << "4. Algorytm Brute force - Przeglad zupelny\n";
        cout << "5. Algorytm Branch&Bound\n";
        cout << "6. Algorytm Branch&Bound z limitem czasowym\n";
        cout << "7. Algorytm DynamicPrograming\n";
        cout << "0. Wroc\n";
        cout << "Wybierz opcje: ";
        cin >> chooseOption; //wybrana opcje

        switch (chooseOption)
        {
            case 1:
                cout << "Pobieranie grafu z pliku tekstowego. Podaj nazwe pliku: ";
                {
                    string filename;
                    cin >> filename;
                    AdjacencyMatrix* newMatrix;
                    newMatrix = FileClass::matrixFromFile(filename);
                    if (newMatrix != nullptr)   // jeśli nie wystąpił błąd, usuń macierz i zastąp ją nową
                    {
                        delete matrix;
                        matrix = newMatrix;
                    }
                    else
                        cout<< "ERROR IN READ"<<endl;
                }
                break;
            case 2:
                cout << "Podaj liczbe wierzcholkow: ";
                cin >> help;
                delete matrix;
                matrix = new AdjacencyMatrix(help,0,true);
                break;
            case 3:	//WYŚWIETL GRAF
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else matrix->printMatrix();
                break;
            case 4: //Brute force
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    BruteForce* bf = new BruteForce(matrix);
                    timer.run();
                    int *heap = bf->main();
                    timer.stop();
                    int cost = 0;
                    cout << endl << "Czas (Brute Force):" << timer.getTimeMs() << " ms" << endl;
                    cout << "Optymalna sciezka:" << endl;
                    for (int i = 0; i < matrix->getNodesCount(); ++i) {
                        cout << heap[i] << " -> ";
                    }
                    cout << matrix->getStartNode() << "\nKoszt: ";
                    for (int i = 0; i < matrix->getNodesCount() - 1; ++i) {
                        cost += matrix->getWsk()[heap[i]][heap[i+1]];
                    }
                    cost += matrix->getWsk()[heap[matrix->getNodesCount()-1]][matrix->getStartNode()];
                    cout << cost;
                    delete[] heap;
                    delete bf;
                }
            }
                break;
            case 5: //Branch&Bound
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    BranchAndBound* bb = new BranchAndBound(matrix);

                    timer.run();
                    list<NodeBB*> listEnd = bb->main();
                    timer.stop();

                    int* pathTable = new int[matrix->getNodesCount()];
                    NodeBB* helpNode = listEnd.back();
                    cout << endl << "Czas (BB):" << timer.getTimeMs() << " ms" << endl;
                    cout << "Optymalna sciezka:" << endl;
                    for (int i = matrix->getNodesCount() - 1; i >= 0; --i) {
                        pathTable[i] = helpNode->numberOfNode;
                        helpNode = helpNode->father;
                    }
                    for (int i = 0; i < matrix->getNodesCount(); ++i) {
                        cout << pathTable[i] << " -> ";
                    }

                    cout << matrix->getStartNode() << "\nKoszt: ";
                    cout << listEnd.back()->lowerBound <<endl;

                    bb->clear();
                    delete bb;
                    delete [] pathTable;
                }
            }
                break;
            case 6: //B&B z limitem czasowym
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    BranchAndBound* bb = new BranchAndBound(matrix);

                    timer.run();

                    list<NodeBB*> listEnd = bb->mainStop();

                    timer.stop();
                    if (listEnd.empty())
                    {
                        cout <<"Przekroczono ustalony limit czasu! "<<endl;
                    } else
                    {
                        int * pathTable = new int[matrix->getNodesCount()];
                        NodeBB* helpNode = listEnd.back();
                        cout << endl << "Czas (BB):" << timer.getTimeMs() << " ms" << endl;
                        cout << "Optymalna sciezka:" << endl;
                        for (int i = matrix->getNodesCount() - 1; i >= 0; --i) {
                            pathTable[i] = helpNode->numberOfNode;
                            helpNode = helpNode->father;
                        }
                        for (int i = 0; i < matrix->getNodesCount(); ++i) {
                            cout << pathTable[i] << " -> ";
                        }

                        cout << matrix->getStartNode() << "\nKoszt: ";
                        cout << listEnd.back()->lowerBound <<endl;

                        delete [] pathTable;
                    }

                    bb->clear();
                    delete bb;
                }
            }
                break;
            case 7:
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    DynamicPrograming* dp = new DynamicPrograming(matrix);

                    timer.run();
                    dp->main();
                    timer.stop();

                    cout << endl << "Czas (DP):" << timer.getTimeMs() << " ms" << endl;
                    dp->printResults();
                    delete dp;
                }
            }
                break;
            case 0:
                system("cls");
                break;
            default:
                cout << endl << "Podano niepoprawna opcje!" << endl;
                break;
        }
        cout << endl << endl;
    } while (chooseOption);

    //usuń tablice po zakonczeniu
    delete matrix;
}
void Menu::showMenuManualM() {
    AdjacencyMatrix* matrix = nullptr;
    Timer timer;
    int chooseOption = 0;
    double stop = 30.0;
    //TS
    int iterationsWithNoChange = 100;
    double k = 1;
    int typeNeigh = 1;
    int aspiration = 0;
    //SA
    double a = 0.999;
    double b = 0.999;
    int c = 5;
    double d = 0.999;
    int iterationsWithNoChangeSA = 1000;

    int bestKnownResult = -1;
    string typeN = "SWAP";

    vector<int> path;
    int help = 0;
    string filename;

    do
    {
        cout << "1. Wczytaj graf z pliku\n";
        cout << "2. Wprowadz kryteria (TS: " << stop << "s Stop, MAXIterationsNoChange = " << iterationsWithNoChange << ", k = " << k <<", aspirationPlus = " <<aspiration
        <<")\n                     (SA: " << stop << "s Stop, a = " << a <<")\n";
        cout << "3. Wybor sasiedztwa ("<<typeN<<")\n";
        cout << "4. Tabu Search\n";
        cout << "5. SimulatedAnnealing\n";
        cout << "6. Wczytaj sciezke z .txt i podaj koszt\n";
        cout << "0. Wroc\n";
        cout << "Wybierz opcje: ";
        cin >> chooseOption; //wybrana opcje

        switch (chooseOption)
        {
            case 1:
                cout << "Pobieranie grafu z pliku tekstowego. Podaj nazwe pliku: ";
                {
                    cin >> filename;
                    AdjacencyMatrix* newMatrix;
                    newMatrix = FileClass::matrixFromFile(filename);
                    if (newMatrix != nullptr)   // jeśli nie wystąpił błąd, usuń macierz i zastąp ją nową
                    {
                        delete matrix;
                        matrix = newMatrix;
                    }
                    else
                        cout<< "ERROR IN READ"<<endl;
                }
                break;
            case 2: //Kryterium stopu
            {
                cout << "\nPodaj czas w sekundach: ";
                cin >> stop;
                cout << "1. Dla Tabu Search\n";
                cout << "2. Dla Symulowanego wyzarzania\n";
                cout << "Wybierz opcje: ";
                cin >> chooseOption; //wybrana opcje
                switch (chooseOption) {
                    case 1:
                        cout << "\nPodaj maksymalna ilosc iteracji bez zmian: ";
                        cin >> iterationsWithNoChange;
                        cout << "\nPodaj k (kadencja = k*sqrt(n)): ";
                        cin >> k;
                        cout << "\nPodaj wielkosc aspiracji: ";
                        cin >> aspiration;
                        break;
                    case 2:
                        cout << "\nPodaj a, gdzie T+1 = a * T: ";
                        cin >> a;
                        break;
                    default:
                        cout << endl << "Podano niepoprawna opcje!" << endl;
                        break;
                }
            }
                break;
            case 3: //sąsiedztwo
            {
                cout << "\nPodaj typ sasiedztwa (1-SWAP,2-INSERT,3-INVERT): ";
                cin >> typeNeigh;
                if (typeNeigh<1 || typeNeigh>3)
                {
                    typeN = "SWAP";
                    typeNeigh = 1;
                    cout << endl << "Podano niepoprawna opcje!" << endl;
                } else if (typeNeigh == 1)
                    typeN = "SWAP";
                else if (typeNeigh == 2)
                    typeN = "INSERT";
                else
                    typeN = "INVERT";

            }
                break;
            case 4: //Tabu search
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    if (filename.find("ftv55") != -1)
                        bestKnownResult = 1608;
                    else if (filename.find("ftv170") != -1)
                        bestKnownResult = 2755;
                    else if (filename.find("rbg358") != -1)
                        bestKnownResult = 1163;
                    else
                        bestKnownResult = -1;

                    TabuSearch* ts = new TabuSearch(matrix, bestKnownResult,stop, iterationsWithNoChange, k, typeNeigh, aspiration);

                    ts->start();
                    path = ts->getShortestPath();
                    ts->printResults();
                    string s = "../Files/Output/ts_";
                    size_t pos = filename.find_last_of('/');
                    size_t pos2 = filename.find_last_of('.');
                    s += filename.substr(pos+1,pos2);
                    s += "_";
                    s += std::to_string(ts->getPathValue());
                    s += ".txt";
                    if (FileClass::saveToFile(s,path,matrix->getNodesCount()+1))
                        cout << "ZAPISANO DO PLIKU\n";
                    else
                        cout << "ERROR IN SAVE\n";
                    delete ts;
                }
            }
                break;
            case 5:
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    if (filename.find("ftv55") != -1)
                        bestKnownResult = 1608;
                    else if (filename.find("ftv170") != -1)
                        bestKnownResult = 2755;
                    else if (filename.find("rbg358") != -1)
                        bestKnownResult = 1163;
                    else
                        bestKnownResult = -1;

                    SimulatedAnnealing* sa = new SimulatedAnnealing(matrix,bestKnownResult,stop,typeNeigh,a);

                    sa->start();
                    path = sa->getShortestPath();
                    sa->printResults();
                    string s = "../Files/Output/sa_";
                    size_t pos = filename.find_last_of('/');
                    size_t pos2 = filename.find_last_of('.');
                    s += filename.substr(pos+1,pos2);
                    s += "_";
                    s += std::to_string(sa->getPathValue());
                    s += ".txt";
                    if (FileClass::saveToFile(s,path,matrix->getNodesCount()+1))
                        cout << "ZAPISANO DO PLIKU\n";
                    else
                        cout << "ERROR IN SAVE\n";
                    delete sa;
                }
            }
                break;
            case 6:
                if (matrix != nullptr) {
                    cout << "Pobieranie sciezki z pliku tekstowego. Podaj nazwe pliku: ";
                    {
                        string filename2;
                        cin >> filename2;
                        vector<int> path2(FileClass::readPathFile(filename2));
                        if (!path2.empty())   // jeśli nie wystąpił błąd, usuń macierz i zastąp ją nową
                        {
                            int helpCount = 0;
                            for (int i = 0; i < matrix->getNodesCount(); i++) {
                                //zliczanie całej wartości ścieżki. Jeśli dojdziemy do ostatniego wierzchołka w ścieżce, policz powrót
                                helpCount += matrix->getWsk()[path2[i]][path2[i + 1]];
                                cout << path2[i] << "->";
                            }
                            cout << path2[matrix->getNodesCount()];
                            cout << "\nKOSZT: " << helpCount;
                            cout << endl;
                        } else
                            cout << "ERROR IN READ" << endl;
                    }
                } else
                    cout <<"BRAK MACIERZY\n";
                break;
            case 0:
                system("cls");
                break;
            default:
                cout << endl << "Podano niepoprawna opcje!" << endl;
                break;
        }
        cout << endl << endl;
    } while (chooseOption);

    //usuń tablice po zakonczeniu
    delete matrix;
}
void Menu::showMenuManualGA() {
    AdjacencyMatrix* matrix = nullptr;
    Timer timer;
    int chooseOption = 0;

    /// WSPÓŁCZYNNIKI
    double stop = 30.0;
    double alphaMutation = 0.01;
    double alphaCross = 0.85;
    int populationSize = 100;
    int tournamentSize = 10;
    int crossType = 0;
    int mutationType = 0;
    string crossTypeS = "OX";
    string mutationTypeS = "INSERT";

    int bestKnownResult = -1;

    vector<int> path;
    int help = 0;
    string filename;

    do
    {
        cout << "1. Wczytaj graf z pliku\n";
        cout << "2. Genetic Algorithm\n";
        cout << "3. Kryterium stopu ("<<stop<<" s)\n";
        cout << "4. Wielkosc populacji poczatkowej ("<<populationSize<<")\n";
        cout << "5. Wielkosc turnieju ("<<tournamentSize<<")\n";
        cout << "6. Wspolczynnik mutacji ("<<alphaMutation<<")\n";
        cout << "7. Wspolczynnik krzyzowania ("<<alphaCross<<")\n";
        cout << "8. Metoda krzyzowania ("<<crossTypeS<<")\n";
        cout << "9. Metoda mutacji ("<<mutationTypeS<<")\n";
        cout << "0. Wroc\n";
        cout << "Wybierz opcje: ";
        cin >> chooseOption; //wybrana opcje

        switch (chooseOption)
        {
            case 1:
                cout << "Pobieranie grafu z pliku tekstowego. Podaj nazwe pliku: ";
                {
                    cin >> filename;
                    AdjacencyMatrix* newMatrix;
                    newMatrix = FileClass::matrixFromFile(filename);
                    if (newMatrix != nullptr)   // jeśli nie wystąpił błąd, usuń macierz i zastąp ją nową
                    {
                        delete matrix;
                        matrix = newMatrix;
                    }
                    else
                        cout<< "ERROR IN READ"<<endl;
                }
                break;
            case 2: // GA
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    if (filename.find("ftv55") != -1)
                        bestKnownResult = 1608;
                    else if (filename.find("ftv170") != -1)
                        bestKnownResult = 2755;
                    else if (filename.find("rbg358") != -1)
                        bestKnownResult = 1163;
                    else
                        bestKnownResult = -1;

                    auto * ga = new GeneticAlgorithm(matrix,alphaMutation,alphaCross,populationSize,crossTypeS,mutationTypeS,stop,bestKnownResult);

                    ga->startAlgorithm();
                    ga->printResults();
                    delete ga;
                }
            }
                break;
            case 3: // STOP
                cout << "\nPodaj czas w sekundach: ";
                cin >> stop;
                break;
            case 4: // POPULACJA
                cout << "\nPodaj wielkosc populacji: ";
                cin >> populationSize;
                break;
            case 5: // POPULACJA
                cout << "\nPodaj wielkosc turnieju: ";
                cin >> tournamentSize;
                break;
            case 6: // MUTACJA ALPHA
                cout << "\nPodaj wpolczynnik mutacji: ";
                cin >> alphaMutation;
                break;
            case 7: // KRZYŻOWKA ALPHA
                cout << "\nPodaj wpolczynnik krzyzowania: ";
                cin >> alphaCross;
                break;
            case 8: // METODA KRZYŻOWANIA
                break;
            case 9: // METODA MUTACJI
                cout << "\n1. INSERT\n";
                cout << "2. SWAP\n";
                cin >> mutationType;
            switch (mutationType) {
                case 1:
                    mutationTypeS = "INSERT";
                    break;
                case 2:
                    mutationTypeS = "SWAP";
                    break;
                default:
                    cout <<"zly numer\n\n";
            }
                break;
            case 0:
                system("cls");
                break;
            default:
                cout << endl << "Podano niepoprawna opcje!" << endl;
                break;
        }
        cout << endl << endl;
    } while (chooseOption);

    //usuń tablice po zakonczeniu
    delete matrix;
}

void Menu::autoBF(int* data, int dataCount)
{
    double time= 0.0;
    fstream file;
    Timer timer;
    AdjacencyMatrix* matrix;

    file.open("../Files/Output/test_BF.txt",ios::out);
    //ilość wierzchołków;średnia z 100 pomiarów
    for (int i = 0; i < dataCount; ++i) {
        file << data[i] <<';';
        for (int k = 0; k < 100; ++k) {
            cout <<"TEST (BF): " <<data[i] <<" wierzcholkow, "<<k<<" instancja: ";
            matrix = new AdjacencyMatrix(data[i],0, true);
            BruteForce* bf = new BruteForce(matrix);
            timer.run();
            int* heap = bf->main();
            timer.stop();
            time += timer.getTimeMs();
            cout << "X\n";
            delete matrix;
            delete bf;
            delete [] heap;
        }
        file << time/100 << '\n';
        time = 0.0;
    }
    file.close();
}

void Menu::autoBB(int *data, int dataCount) {
    double time= 0.0;
    fstream file;
    Timer timer;
    AdjacencyMatrix* matrix;

    file.open("../Files/Output/test_BB.txt",ios::out);
    //ilość wierzchołków;średnia z 100 pomiarów;ilość obliczonych w czasie 20s
    for (int i = 0; i < dataCount; ++i) {
        file << data[i] <<';';
        int counter = 0;
        for (int k = 0; k < 100; ++k) {
            cout <<"TEST (BB): " <<data[i] <<" wierzcholkow, "<<k<<" instancja: ";
            matrix = new AdjacencyMatrix(data[i],0, true);
            BranchAndBound* bb = new BranchAndBound(matrix);

            timer.run();

            list<NodeBB*> listEnd = bb->mainStop();
            timer.stop();

            if (!listEnd.empty())
            {
                time += timer.getTimeMs();
                counter++;
                cout << counter;
                cout << "X\n";
            } else
                cout << " -\n";

            bb->clear();
            delete matrix;
            delete bb;
        }
        file << time/counter << ";" <<counter <<'\n';
        time = 0.0;
    }
    file.close();
}

void Menu::autoDP(int *data, int dataCount) {
    double time= 0.0;
    fstream file;
    Timer timer;
    AdjacencyMatrix* matrix;
    file.open("../Files/Output/test_DP.txt",ios::out);
    //ilość wierzchołków;średnia z 100 pomiarów
    for (int i = 0; i < dataCount; ++i) {
        file << data[i] <<';';
        for (int k = 0; k < 100; ++k) {
            cout <<"TEST (DP): " <<data[i] <<" wierzcholkow, "<<k<<" instancja: ";
            matrix = new AdjacencyMatrix(data[i],0, true);
            DynamicPrograming* dp = new DynamicPrograming(matrix);
            timer.run();
            dp->main();
            timer.stop();
            time += timer.getTimeMs();
            cout << "X\n";
            delete matrix;
            delete dp;
        }
        file << time/100 << '\n';
        time = 0.0;
    }
    file.close();
}

void Menu::autoTS(string data[], int timeData[], int iterationsNoChange, double p, int dataCount, int typeNeigh, int aspiration)
{
    fstream file;
    TabuSearch* ts;
    AdjacencyMatrix* matrix;
    vector<int> bestPath;
    vector<vector<double>> bestPathChanging;
    int bestPathValue = INT32_MAX;
    int timeBest= 0;
    int l = 0;

    if (typeNeigh == 0)
    {
        l = 1;
        typeNeigh = 3;
    }
    else
        l = typeNeigh;

    file.open("../Files/Output/test_TS.txt",ios::out | ios::app);
    //nazwa pliku;najlepsze rozwizanie;czas;sąsiedztwo;MAXiteracjeNoChange;Kadencja;VALUE1;TIME1;VALUE2;TIME2....
    for (; l <= typeNeigh; ++l) {
        for (int i = 0; i < dataCount; ++i) {
            file << data[i] << ';';
            matrix = FileClass::matrixFromFile(data[i]);
            bestPath.clear();
            bestPath.resize(matrix->getNodesCount() + 1);

            if (data[i].find("ftv55") != -1)
            {
                iterationsNoChange = 150;
                p = 0.65;
                aspiration = 0;
            }
            else if (data[i].find("ftv170") != -1)
            {
                iterationsNoChange = 240;
                p = 3.4;
                aspiration = 60;
            }
            else if (data[i].find("rbg358") != -1)
            {
                iterationsNoChange = 290;
                p = 2;
                aspiration = 20;
            }

            for (int k = 0; k < 10; ++k) {
                cout << "TEST (TS): " << data[i] << ", " << k << " proba: ";
                ts = new TabuSearch(matrix,-1, timeData[i], iterationsNoChange, p, l, aspiration);
                ts->start();
                if (ts->getPathValue() < bestPathValue) {
                    bestPathValue = ts->getPathValue();
                    timeBest = ts->getTime();
                    bestPath = ts->getShortestPath();
                    bestPathChanging = ts->getPathChanging();
                }
                cout << "X\n";
                delete ts;
            }
            string s = "../Files/Output/ts_";
            size_t pos = data[i].find_last_of('/');
            size_t pos2 = data[i].find_last_of('.');
            s += data[i].substr(pos + 1, pos2);
            s += "_";
            s += std::to_string(bestPathValue);
            s += ".txt";
            if (FileClass::saveToFile(s, bestPath, matrix->getNodesCount() + 1))
                cout << "ZAPISANO DO PLIKU\n";
            else
                cout << "ERROR IN SAVE\n";

            file << bestPathValue << ";" << timeBest << ";" << l << ";" << iterationsNoChange << ";" << p <<";" <<aspiration<<";";

            for (vector<double> g: bestPathChanging) {
                file << g.at(0) << ";" << g.at(1) <<";";
            }
            file << endl;

            bestPathValue = INT32_MAX;
        }
    }
    file.close();
}
void Menu::autoSA(std::string data[], int timeData[], double* a, int typeNeigh,int dataCount)
{
    fstream file;
    SimulatedAnnealing* sa;
    AdjacencyMatrix* matrix;
    vector<int> bestPath;
    vector<vector<double>> bestPathChanging;
    int bestPathValue = INT32_MAX;
    int timeBest= 0;
    int L = 0;
    int l = 0;
    double tempStart = 0.0;
    double tempEnd = 0.0;

    if (typeNeigh == 0)
    {
        l = 0;
        typeNeigh = 3;
    }
    else
        l = typeNeigh;

    file.open("../Files/Output/test_SA.txt",ios::out | ios::app);
    //nazwa pliku;najlepsze rozwizanie;czas;rozmiar ery;a;TempSTART;TempEND;VALUE1;TIME1;VALUE2;TIME2....
    for (; l < typeNeigh; ++l) {
        for (int i = 0; i < dataCount; ++i) {
            file << data[i] << ';';
            matrix = FileClass::matrixFromFile(data[i]);
            bestPath.clear();
            bestPath.resize(matrix->getNodesCount() + 1);

            for (int k = 0; k < 1; ++k) {
                cout << "TEST (SA): " << data[i] << ", " << k << " proba: ";
                sa = new SimulatedAnnealing(matrix,-1,timeData[i],2,a[l]);
                sa->start();
                if (sa->getPathValue() < bestPathValue) {
                    bestPathValue = sa->getPathValue();
                    timeBest = sa->getTime();
                    bestPath = sa->getShortestPath();
                    bestPathChanging = sa->getPathChanging();
                    tempStart = sa->getTempStart();
                    tempEnd = sa->getTempEnd();
                    L = sa->getL();
                }
                cout << "X\n";
                delete sa;
            }
            string s = "../Files/Output/sa_";
            size_t pos = data[i].find_last_of('/');
            size_t pos2 = data[i].find_last_of('.');
            s += data[i].substr(pos + 1, pos2);
            s += "_";
            s += std::to_string(bestPathValue);
            s += ".txt";
            if (FileClass::saveToFile(s, bestPath, matrix->getNodesCount() + 1))
                cout << "ZAPISANO DO PLIKU\n";
            else
                cout << "ERROR IN SAVE\n";

            file << bestPathValue << ";" << timeBest << ";" << L << ";" << a[l]<<";" << tempStart << ";" << tempEnd <<";";

            for (vector<double> g: bestPathChanging) {
                file << g.at(0) << ";" << g.at(1) <<";";
            }
            file << endl;

            bestPathValue = INT32_MAX;
        }
    }
    file.close();
}

void Menu::autoGA(vector<string>& data, const vector<int>& timeData, const vector<int>& populationSize,
                  const vector<string>& mutationStrategy, const vector<double>& mutationRate, const vector<string>& crossStrategy,
                  const vector<double>& crossRate, int bestKnown, int iterations)
{
    fstream file;
    GeneticAlgorithm* ga;
    AdjacencyMatrix* matrix;
    vector<int> bestPath;
    vector<vector<double>> bestPathChanging;
    int bestPathValue = INT32_MAX;
    double timeBest= 0;
    int tournamentSize = 10;

    file.open("../Files/Output/test_GA.txt",ios::out | ios::app);
    //nazwa pliku;najlepsze rozwizanie;czas;rozmiar populacji;rozmiar turnieju;mutationStrategy;mutationRate;crossStrategy;crossRate;VALUE1;TIME1;VALUE2;TIME2....
    for (int i : populationSize) {
        for (const auto & j : mutationStrategy) {
            for (double k : mutationRate) {
                for (const auto & l : crossStrategy) {
                    for (double m : crossRate) {
                        for (int n = 0; n < data.size(); ++n) {
                            file << data[n] << ';';
                            matrix = FileClass::matrixFromFile(data[n]);
                            bestPath.clear();
                            bestPath.resize(matrix->getNodesCount() + 1);
                            for (int i1 = 0; i1 < iterations; ++i1) {
                                cout << "TEST (GA): " << data[n] << ", " << i1 << " proba: ";
                                ga = new GeneticAlgorithm(matrix,k,m,
                                                          i,l,
                                                          j,timeData[n],bestKnown);
                                ga->startAlgorithm();
                                if (ga->bestKnownResult < bestPathValue) {
                                    bestPathValue = ga->bestKnownResult;
                                    timeBest = ga->bestValueTime;
                                    bestPath = ga->bestTour.nodes;
                                    bestPathChanging = ga->shortestPathChanging;
                                    tournamentSize = ga->tournamentSize;
                                }
                                cout << "X\n";
                                delete ga;
                            }
                            string s = "../Files/Output/ga_";
                            size_t pos = data[n].find_last_of('/');
                            size_t pos2 = data[n].find_last_of('.');
                            s += data[n].substr(pos + 1, pos2);
                            s += "_";
                            s += std::to_string(bestPathValue);
                            s += ".txt";
                            if (FileClass::saveToFile(s, bestPath, matrix->getNodesCount() + 1))
                                cout << "ZAPISANO DO PLIKU\n";
                            else
                                cout << "ERROR IN SAVE\n";

                            //najlepsze rozwizanie;czas;rozmiar populacji;rozmiar turnieju;mutationStrategy;mutationRate;crossStrategy;crossRate;VALUE1;TIME1;VALUE2;TIME2....
                            file << bestPathValue << ";" << timeBest << ";" << i << ";" << tournamentSize
                            <<";" << j << ";" << k <<";" << l <<";" << m <<";";

                            for (vector<double> g: bestPathChanging) {
                                file << g.at(0) << ";" << g.at(1) <<";";
                            }
                            file << endl;

                            bestPathValue = INT32_MAX;
                        }
                    }
                }
            }
        }
    }
    file.close();
}
